#include "InnerMessageDispatcher.h"
#include "MessageDispatcherComponent.h"


void InnerMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t msg_id = 0;
	if (len < sizeof(msg_id))
		throw std::exception(std::format("���ݽ���������Ϊû��ȷ����Ϣid��(session->Address() = '%s')", session->Address.ToString().c_str()).c_str());


	auto& appType = Game::Options().AppType;
	auto& message_state = MessageDispatcherComponent::Instance->__m_message;


}
