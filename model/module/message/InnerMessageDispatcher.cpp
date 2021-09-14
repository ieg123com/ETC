#include "InnerMessageDispatcher.h"
#include "OpcodeTypeComponent.h"
#include "InnerMessageDispatcherHandler.h"
#include "net/Session.h"


void InnerMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	// 内外消息头结构
	// opcode		2 bytes
	// actor_id		8 bytes
	uint16_t opcode = 0;
	int64_t actor_id = 0;
	const char* pos = data;
	size_t size = len;
	if (len < (sizeof(opcode) + sizeof(actor_id)))
		throw std::exception(std::format("InnerMessageDispatcher 数据解析错误，因为没法确定消息头格式不合法！(session->Address = '%s')", session->Address.ToString().c_str()).c_str());

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
		// 内网收到了外网的消息，可能是其他服务发的，让gate转发给玩家。或者gate广播的消息
		auto obj = Game::Event().GetObject(actor_id);
		if (obj == nullptr)
		{
			// 没有找到acotr
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
			// 转发给客户端
			gate_session->Send(opcode, pos, size);
			return;
		}
	}


	auto proto_message = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);
	if (!proto_message->ParseFromArray(pos, size))
	{

		throw std::exception(
			std::format(
				"解析消息失败! message type = %s",
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
			if (session->InstanceId() != instance_id)return;// 在处理消息的这段时间，会话已经被断开了
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
