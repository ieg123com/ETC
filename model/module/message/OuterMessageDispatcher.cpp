#include "OuterMessageDispatcher.h"
#include "MessageDispatcherComponent.h"



void OuterMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t msg_id = 0;
	if (len < sizeof(msg_id))
		throw std::exception(std::format("���ݽ���������Ϊû��ȷ����Ϣid��(session->Address() = '%s')", session->Address.ToString().c_str()).c_str());


	auto& appType = Game::Options().AppType;
	auto& message_state = MessageDispatcherComponent::Instance->__m_message;
	if (!Is((EAppType)message_state[msg_id].app_type, appType))
	{
		// ���Ͳ���
		// TODO ����ǲ���Gate
		if (Is(appType, EAppType::Gate))
		{
			// ������

		}
		return;
	}

	switch (message_state[msg_id].msg_type)
	{
	case EMessageType::Message:
		if (auto message = dynamic_cast<IMessageSystem*>(message_state[msg_id].call_back.get()))
		{
			message->Handle(session, data + sizeof(msg_id), len - sizeof(msg_id));
		}
		else {
			throw std::exception(std::format("ע�����Ϣ������ IMessageSystem ����, msg_id = %d", msg_id).c_str());
		}
		break;
	case EMessageType::Request:
		if (auto message = dynamic_cast<IRpcMessageSystem*>(message_state[msg_id].call_back.get()))
		{
			message->Handle(session, data + sizeof(msg_id), len - sizeof(msg_id));
		}
		else {
			throw std::exception(std::format("ע�����Ϣ������ IRpcMessageSystem ����, msg_id = %d", msg_id).c_str());
		}
		break;
	}



}