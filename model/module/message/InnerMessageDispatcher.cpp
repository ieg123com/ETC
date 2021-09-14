#include "InnerMessageDispatcher.h"
#include "OpcodeTypeComponent.h"
#include "InnerMessageDispatcherHandler.h"
#include "net/Session.h"


void InnerMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	// ������Ϣͷ�ṹ
	// opcode		2 bytes
	// actor_id		8 bytes
	uint16_t opcode = 0;
	int64_t actor_id = 0;
	const char* pos = data;
	size_t size = len;
	if (len < (sizeof(opcode) + sizeof(actor_id)))
		throw std::exception(std::format("InnerMessageDispatcher ���ݽ���������Ϊû��ȷ����Ϣͷ��ʽ���Ϸ���(session->Address = '%s')", session->Address.ToString().c_str()).c_str());

	memcpy(&opcode, pos, sizeof(opcode));
	pos += sizeof(opcode);
	size -= sizeof(opcode);
	memcpy(&actor_id, pos, sizeof(actor_id));
	pos += sizeof(actor_id);
	size -= sizeof(actor_id);

	EMessageType msg_type = OpcodeTypeComponent::Instance->GetMessageType(opcode);
	if (msg_type == EMessageType::None)
	{
		return;
	}
	if (OpcodeTypeComponent::Instance->IsOuterActorMessage(opcode))
	{
		// �����յ�����������Ϣ���������������񷢵ģ���gateת������ҡ�����gate�㲥����Ϣ
		auto obj = Game::Event().GetObject(actor_id);
		if (obj == nullptr)
		{
			// û���ҵ�acotr
			if (auto proto_message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode))
			{
				LOG_ERROR("not found actor: {}  {}",
					actor_id,
					proto_message->GetType().full_name());
			}
			else {
				LOG_ERROR("not found actor: {}  opcode: {}",
					actor_id,
					opcode);
			}
			return;
		}

		if (auto gate_session = dynamic_cast<Session*>(obj.get()))
		{
			// ת�����ͻ���
			gate_session->Send(opcode, pos, size);
			return;
		}
	}


	auto proto_message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);
	if (!proto_message->ParseFromArray(pos, size))
	{

		throw std::exception(
			std::format(
				"������Ϣʧ��! message type = %s",
				proto_message->GetType().full_name()).c_str());
	}
	switch (msg_type)
	{
	case EMessageType::IActorMessage:
	{
		auto message = std::dynamic_pointer_cast<IActorMessage>(proto_message);
		InnerMessageDispatcherHandler::HandleIActorMessage(actor_id, message);
	}
		break;
	case EMessageType::IActorRequest:
	case EMessageType::IActorLocationMessage:
	case EMessageType::IActorLocationRequest:
	{
		auto request = std::dynamic_pointer_cast<IActorRequest>(proto_message);
		InstanceID instance_id = session->InstanceId();
		FMPReply reply = [=](IResponse* response)->void {
			if (session->InstanceId() != instance_id)return;// �ڴ�����Ϣ�����ʱ�䣬�Ự�Ѿ����Ͽ���
			response->SetRpcId(request->GetRpcId());
			session->Reply(response);
		};
		InnerMessageDispatcherHandler::HandleIActorRequest(actor_id, request, reply);
	}
		break;
	case EMessageType::IActorResponse:
	case EMessageType::IActorLocationResponse:

		auto response = std::dynamic_pointer_cast<IActorResponse>(proto_message);
		InnerMessageDispatcherHandler::HandleIActorResponse(actor_id, response);
		break;
	}

}
