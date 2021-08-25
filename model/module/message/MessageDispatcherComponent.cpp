#include "MessageDispatcherComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"


namespace Model
{
	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;



	void MessageDispatcherComponent::Awake()
	{
		__m_message.resize(UINT16_MAX + 1);

	}

	void MessageDispatcherComponent::Clear()
	{
		__m_message_id.clear();
		for (auto& item : __m_message)item.clear();
	}

	void MessageDispatcherComponent::Handle(const uint16_t msg_id, const char* data, const char* len)
	{
		auto& appType = StartConfigComponent::Instance->startConfig->AppType;
		if (Is((EAppType)__m_message[msg_id].msg_type, appType))
		{
			// 类型不符
			// 检查是不是Gate




			return;
		}
	
	}


}