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
					auto found_type_req = self->__m_message_id.find(item->GetRequestType());
					if (found_type_req == self->__m_message_id.end())
					{
						LOG_WARN("û��ע�����Ϣ���� {}", item->GetRequestType().class_name());
						continue;
					}
					self->__m_message[found_type_req->second].call_back = item;
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}

