#include "OuterMessageDispatcher.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"
#include "net/Session.h"
#include "module/component/SessionPlayerComponent.h"
#include "module/actorlocation/ActorLocationSenderComponent.h"



void OuterMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t opcode = 0;
	const char* pos = data;
	size_t size = len;
	if (len < sizeof(opcode))
		throw std::exception(std::format("OuterMessageDispatcher ���ݽ���������Ϊû��ȷ����Ϣid��(session->Address() = '%s')", session->RemoteAddress.ToString().c_str()).c_str());

	memcpy(&opcode, data, sizeof(opcode));
	pos += sizeof(opcode);
	size -= sizeof(opcode);
	LOG_WARN("msg id:{}", opcode);

	EMessageType msg_type = OpcodeTypeComponent::Instance->GetMessageType(opcode);
	if (msg_type == EMessageType::None)
	{
		LOG_WARN("�յ�һ��δ֪��Ϣ����,opcode = {}", opcode);
		return;
	}

	auto proto_msg = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);

	if (!proto_msg->ParseFromArray(pos, size))
	{
		// ����ʧ��,�޷���ȡRpcId����˲��Դ˽��лظ�
		return;
	}

	switch (msg_type)
	{
	case EMessageType::IMessage:
	case EMessageType::IRequest:
	{
		MessageDispatcherComponent::Instance->Handle(session, opcode, proto_msg.get());
		break;
	}
	case EMessageType::IActorLocationMessage:
	{
		{
			ID key = session->GetComponent<SessionPlayerComponent>()->GetIdByOpcode(opcode);
			ActorLocationSenderComponent::Instance->Send(key, std::dynamic_pointer_cast<IActorRequest>(proto_msg));
			break;
		}
		
	}
	case EMessageType::IActorLocationRequest:
	{
		{
			// ActorLocation ��Ϣ�����յ�����Ϣת������Ҫ�ķ�����
			ID key = session->GetComponent<SessionPlayerComponent>()->GetIdByOpcode(opcode);
			auto request = std::dynamic_pointer_cast<IActorRequest>(proto_msg);
			int32_t rpc_id = request->GetRpcId();
			InstanceID instance_id = session->InstanceId();
			auto response = ActorLocationSenderComponent::Instance->Call<IActorResponse>(key, request);
			if (instance_id == session->InstanceId())
			{
				response->SetRpcId(rpc_id);
				session->Reply(response.get());
			}
			break;
		}
	}
	default:
		break;
	}



}