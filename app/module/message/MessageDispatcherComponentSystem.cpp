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
				// TODO:  给指定消息id设置回调函数
				auto& message_system = Game::Event().__message_system;
				for (auto& item : message_system)
				{
					// 请求消息
					try
					{
						uint16_t opcode = OpcodeTypeComponent::Instance->GetTypeOpcodeTry(item->GetRequestType());
						self->GetMessage(opcode).app_type = item->appType;
						self->GetMessage(opcode).call_back = item;
					}
					catch (std::exception& e)
					{
						LOG_WARN("没有注册的消息类型 {} error:{}", item->GetRequestType().class_name(),e.what());
					}
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


