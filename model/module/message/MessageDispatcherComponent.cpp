#include "MessageDispatcherComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "net/Session.h"



namespace Model
{
	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;



	void MessageDispatcherComponent::Awake()
	{
		m_messages.resize(UINT16_MAX + 1);

	}

	void MessageDispatcherComponent::Clear()
	{
		for (auto& item : m_messages)item.clear();
	}
}

