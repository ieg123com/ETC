#include "MessageDispatcherComponent.h"


namespace Model
{
	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;



	void MessageDispatcherComponent::Awake()
	{
		__m_message.resize(UINT16_MAX + 1);

	}

	void MessageDispatcherComponent::Clear()
	{

	}




}