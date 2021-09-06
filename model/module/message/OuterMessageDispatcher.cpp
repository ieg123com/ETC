#include "OuterMessageDispatcher.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"
#include "net/Session.h"



void OuterMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t opcode = 0;
	if (len < sizeof(opcode))
		throw std::exception(std::format("OuterMessageDispatcher ���ݽ���������Ϊû��ȷ����Ϣid��(session->Address() = '%s')", session->Address.ToString().c_str()).c_str());

	memcpy(&opcode, data, sizeof(opcode));
	LOG_WARN("msg id:{}", opcode);

	EMessageType msg_type = OpcodeTypeComponent::Instance->GetMessageType(opcode);
	if (msg_type == EMessageType::None)
	{
		LOG_WARN("�յ�һ��δ֪��Ϣ����,opcode = {}", opcode);
		return;
	}

	auto proto_msg = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);


	switch (msg_type)
	{
	case EMessageType::IMessage:
	{
		MessageDispatcherComponent::Instance->MessageHandle(session, opcode, proto_msg);
	}
	break;
	case EMessageType::IRequest:
	{
		auto msg_req = std::dynamic_pointer_cast<IRequest>(proto_msg);
		if (!msg_req->ParseFromArray(data, len))
		{
			// ����ʧ��,�޷���ȡRpcId����˲��Դ˽��лظ�
			return;
		}
		MessageDispatcherComponent::Instance->MRpcHandle(session, opcode, msg_req);
	}
	break;
	case EMessageType::IActorLocationMessage:
	{

	}
	break;
	case EMessageType::IActorLocationRequest:
	{
		// ActorLocation ��Ϣ�����յ�����Ϣת������Ҫ�ķ�����

	}
	break;
	default:
		break;
	}



}