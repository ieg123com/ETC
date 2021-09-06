#include "MessageDispatcherComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "net/Session.h"
#include "interface/IMessage.h"
#include "interface/IRpcMessage.h"


namespace Model
{

	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;


	void MessageDispatcherComponent::Awake()
	{
		m_message_handler.resize(UINT16_MAX + 1);
		m_mrpc_handler.resize(UINT16_MAX + 1);
	}

	void MessageDispatcherComponent::Clear()
	{
		for (auto& item : m_message_handler)item.reset();
		for (auto& item : m_mrpc_handler)item.reset();
	}

	void MessageDispatcherComponent::RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMSystemHandler> handler)
	{
		if (auto instance = std::dynamic_pointer_cast<IMessageHandler>(handler))
		{
			m_message_handler[opcode] = instance;
		}
		else if(auto instance = std::dynamic_pointer_cast<IMRpcHandler>(handler)) 
		{
			m_mrpc_handler[opcode] = instance;
		}
	}

	void MessageDispatcherComponent::MessageHandle(const std::shared_ptr<Session>& session, const uint16_t opcode, const std::shared_ptr<IMessage>& message)
	{
		if (m_message_handler[opcode])
		{
			m_message_handler[opcode]->Handle(session, message.get());
		}
	}

	void MessageDispatcherComponent::MRpcHandle(const std::shared_ptr<Session>& session, const uint16_t opcode, const std::shared_ptr<IRequest>& request)
	{
		if (m_mrpc_handler[opcode])
		{
			m_mrpc_handler[opcode]->Handle(session, request.get());
		}
	}

}

