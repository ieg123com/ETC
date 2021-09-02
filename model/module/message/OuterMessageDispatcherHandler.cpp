#include "OuterMessageDispatcherHandler.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"


void OuterMessageDispatcherHandler::HandleIMessage(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len)
{
	auto message_state = MessageDispatcherComponent::Instance->GetMessage(opcode);

	if (auto msg_handler = dynamic_cast<IMessageHandler*>(message_state.call_back.get()))
	{
		msg_handler->Handle(session, data, len);
	}
	else {
		throw std::exception(std::format("ע�����Ϣ������ IMessageHandler ����, opcode = %d", opcode).c_str());
	}
}

void OuterMessageDispatcherHandler::HandleIMRequest(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len)
{
	auto message_state = MessageDispatcherComponent::Instance->GetMessage(opcode);

	if (auto msg_handler = dynamic_cast<IMRpcHandler*>(message_state.call_back.get()))
	{
		msg_handler->Handle(session, data, len);
	}
	else {
		throw std::exception(std::format("ע�����Ϣ������ IMRpcHandler ����, opcode = %d", opcode).c_str());
	}
}

void OuterMessageDispatcherHandler::HandleIMActorLocation(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len)
{

}

void OuterMessageDispatcherHandler::HandleIMActorLocationRequest(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len)
{

}