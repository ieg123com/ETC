#include "OuterMessageDispatcher.h"
#include "MessageDispatcherComponent.h"
#include "OuterMessageDispatcherHandler.h"
#include "net/Session.h"



void OuterMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t opcode = 0;
	if (len < sizeof(opcode))
		throw std::exception(std::format("OuterMessageDispatcher 数据解析错误，因为没法确定消息id！(session->Address() = '%s')", session->Address.ToString().c_str()).c_str());

	memcpy(&opcode, data, sizeof(opcode));
	LOG_WARN("msg id:{}", opcode);
	auto& appType = Game::Options().AppType;
	auto& message_state = MessageDispatcherComponent::Instance->GetMessage(opcode);
	if (!Is((EAppType)message_state.app_type, appType))
	{
		// 类型不符
		// TODO 检查是不是Gate
		if (Is(appType, EAppType::Gate))
		{
			// 是网关

		}
		return;
	}

	switch (message_state.msg_type)
	{
	case EMessageType::Message:
		OuterMessageDispatcherHandler::HandleIMessage(session,opcode, data + sizeof(opcode), len - sizeof(opcode));
		break;
	case EMessageType::Request:
		OuterMessageDispatcherHandler::HandleIMRequest(session,opcode, data + sizeof(opcode), len - sizeof(opcode));
		break;
	case EMessageType::ActorLocationMessage:
		OuterMessageDispatcherHandler::HandleIMActorLocation(session,opcode, data + sizeof(opcode), len - sizeof(opcode));
		break;
	case EMessageType::ActorLocationRequest:
		OuterMessageDispatcherHandler::HandleIMActorLocationRequest(session,opcode, data + sizeof(opcode), len - sizeof(opcode));
		break;
	default:
		break;
	}



}