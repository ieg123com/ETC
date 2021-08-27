#include "model/module/message/MessageDispatcherComponent.h"
#include "model/module/other/SystemEventType.h"

using namespace Model;


namespace Hotfix
{

	class MessageDispatcherComponentAwakeSystem :public AwakeSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<MessageDispatcherComponent>& self) override
		{
			LOG_INFO("MessageDispatcherComponent Awake");
			self->Awake();
		}
	};
	REF(MessageDispatcherComponentAwakeSystem, ObjectSystem);

	class MessageDispatcherComponentLoadSystem :public LoadSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<MessageDispatcherComponent>& self)override
		{
			LOG_INFO("MessageDispatcherComponent Load");
			MessageDispatcherComponent::Instance = self.get();
			self->Clear();
			Game::Event().Run<const std::shared_ptr<MessageDispatcherComponent>&>(ESystemEventType::StartRegMessage, self);
			
			{
				// TODO:  
				auto& message_system = Game::Event().__message_system;
				for (auto& item : message_system)
				{
					// 请求消息
					auto found_type_req = self->__m_message_type.find(item->GetRequestType());
					if (found_type_req == self->__m_message_type.end())
					{
						LOG_WARN("没有注册的消息类型 {}", item->GetRequestType().class_name());
						continue;
					}
					found_type_req->second.app_type = item->appType;
					self->__m_message[found_type_req->second.msg_id].call_back = item;
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


