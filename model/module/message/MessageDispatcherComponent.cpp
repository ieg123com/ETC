#include "MessageDispatcherComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "net/Session.h"


namespace Model
{

	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;


	void MessageDispatcherComponent::Awake()
	{
		m_message_handler.resize(UINT16_MAX + 1);
	}

	void MessageDispatcherComponent::Clear()
	{
		for (auto& item : m_message_handler)item.reset();
	}

	void MessageDispatcherComponent::RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMHandler>& handler)
	{
		m_message_handler[opcode] = handler;

	}


	void MessageDispatcherComponent::Handle(const std::shared_ptr<Session>& session, const uint16_t opcode, IMessage* message)
	{
		if (m_message_handler[opcode])
		{
			m_message_handler[opcode]->Handle(session, message);
		}
	}

}

