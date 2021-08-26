#include "MessageDispatcherComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "net/Session.h"


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

	void MessageDispatcherComponent::Handle(const std::shared_ptr<Session>& session, const char* data, const size_t len)
	{
		uint16_t msg_id = 0;
		if (len < sizeof(msg_id))
			throw std::exception(std::format("数据解析错误，因为没法确定消息id！(%s)",session->Address().ToString().c_str()).c_str());


		auto& appType = StartConfigComponent::Instance->startConfig->AppType;
		if (!Is((EAppType)__m_message[msg_id].app_type, appType))
		{
			// 类型不符
			// TODO 检查是不是Gate
			if (Is(appType, EAppType::Gate))
			{
				// 是网关

			}
			return;
		}

		switch (__m_message[msg_id].msg_type)
		{
		case EMessageType::Message:

			break;
		case EMessageType::Request:
			break;
		case EMessageType::Response:
			break;
		case EMessageType::ActorMessage:
			break;
		case EMessageType::ActorRequest:
			break;
		case EMessageType::ActorResponse:
			break;
		}

		//__m_message[msg_id].call_back
	
	}


}