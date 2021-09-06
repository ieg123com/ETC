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
	size += sizeof(opcode);
	memcpy(&actor_id, pos, sizeof(actor_id));
	pos += sizeof(actor_id);
	size += sizeof(actor_id);

	LOG_INFO("opcode = {} actor_id = {} rpc_id = {}", opcode, actor_id);

	EMessageType msg_type = OpcodeTypeComponent::Instance->GetMessageType(opcode);
	if (msg_type == EMessageType::None)
	{
		return;
	}

	auto proto_message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);

	switch (msg_type)
	{
	case EMessageType::IActorMessage:
	case EMessageType::IActorLocationMessage:
	{
		auto message = std::dynamic_pointer_cast<IActorMessage>(proto_message);
		ObjectID obj_id = session->GetObjectID();
		FMPReply reply = [=](IResponse* response)->void {
			if (session->GetObjectID() != obj_id)return;// �ڴ�����Ϣ�����ʱ�䣬�Ự�Ѿ����Ͽ���
			response->SetRpcId(message->GetRpcId());
			session->Reply(response);
		};
		InnerMessageDispatcherHandler::HandleIActorMessage(actor_id, message, reply);
	}
		break;
	case EMessageType::IActorRequest:
	case EMessageType::IActorLocationRequest:
	{
		auto request = std::dynamic_pointer_cast<IActorRequest>(proto_message);
		ObjectID obj_id = session->GetObjectID();
		FMPReply reply = [=](IResponse* response)->void {
			if (session->GetObjectID() != obj_id)return;// �ڴ�����Ϣ�����ʱ�䣬�Ự�Ѿ����Ͽ���
			response->SetRpcId(request->GetRpcId());
			session->Reply(response);
		};
		InnerMessageDispatcherHandler::HandleIActorRequest(actor_id, request, reply);
	}
		break;
	case EMessageType::IActorResponse:
	case EMessageType::IActorLocationResponse:
		InnerMessageDispatcherHandler::HandleIActorResponse(opcode, actor_id, pos, size);
		break;
		
	}

}
