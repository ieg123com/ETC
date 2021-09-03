#include "InnerMessageDispatcher.h"
#include "MessageDispatcherComponent.h"
#include "InnerMessageDispatcherHandler.h"
#include "net/Session.h"


void InnerMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t opcode = 0;
	int64_t actor_id = 0;
	const char* pos = data;
	size_t size = len;
	if (len < sizeof(opcode))
		throw std::exception(std::format("InnerMessageDispatcher 数据解析错误，因为没法确定消息id！(session->Address = '%s')", session->Address.ToString().c_str()).c_str());

	memcpy(&opcode, pos, sizeof(opcode));
	pos += sizeof(opcode);
	size += sizeof(opcode);
	memcpy(&actor_id, pos, sizeof(actor_id));
	pos += sizeof(actor_id);
	size += sizeof(actor_id);

	LOG_INFO("opcode = {} actor_id = {} rpc_id = {}", opcode, actor_id);

	auto& appType = Game::Options().AppType;
	auto& message_state = MessageDispatcherComponent::Instance->GetMessage(opcode);
	if (!Is((EAppType)message_state.app_type, appType))
	{
		return;
	}

	switch (message_state.msg_type)
	{
	case EMessageType::ActorMessage:
	{
		stIMRequest st_req;
		auto message_req = OpcodeTypeComponent::Instance->RequestMessageParse(opcode, st_req, data, len);
		auto reply = [&](PBMessage* response)->void {
			uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetResponseOpcodeTry(opcode);
			stIMResponse st_rpo;
			st_rpo.RpcId = st_req.RpcId;
			OpcodeTypeComponent::Instance->ResetMessageResponse(opcode_rpo, response, st_rpo);
			session->ActorReply(opcode_rpo, actor_id, response);
		};
		InnerMessageDispatcherHandler::HandleIActorMessage(opcode, actor_id, message_req.get(), reply);
	}
		break;
	case EMessageType::ActorRequest:
	{
		stIMRequest st_req;
		auto message_req = OpcodeTypeComponent::Instance->RequestMessageParse(opcode, st_req, data, len);
		auto reply = [&](PBMessage* response)->void {
			uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetResponseOpcodeTry(opcode);
			stIMResponse st_rpo;
			st_rpo.RpcId = st_req.RpcId;
			OpcodeTypeComponent::Instance->ResetMessageResponse(opcode_rpo, response, st_rpo);
			session->ActorReply(opcode_rpo, actor_id, response);
		};
		InnerMessageDispatcherHandler::HandleIActorRequest(opcode, actor_id, message_req.get(), reply);
	}
		break;
	case EMessageType::ActorResponse:
		InnerMessageDispatcherHandler::HandleIActorResponse(opcode, actor_id, pos, size);
		break;
	case EMessageType::ActorLocationMessage:
		break;
	case EMessageType::ActorLocationRequest:
		break;
	case EMessageType::ActorLocationResponse:
		break;
	}

}
