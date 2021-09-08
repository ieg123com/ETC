#include "model/module/message/MessageDispatcherComponent.h"
#include "model/module/other/SystemEventType.h"
#include "model/base/type/type_factory.h"


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

			{
				// 给指定消息id注册回调实例
				auto appTyep = Game::Options().AppType;
				auto proto_message = Game::Event().GetAssemblysType<Message>();
				for (auto& item : proto_message)
				{
					// 这是一个特性实例
					auto attr = std::dynamic_pointer_cast<Message>(item.second);
					// 检查触发器是否支持当前服务
					if (!Is((EAppType)attr->appType, appTyep))continue;
					// 消息处理对象类型。（获取被这个特性实例包装的对象类型）
					Type handler_type = attr->GetObjectType();
					// 消息处理对象实例
					if (auto handler = TypeFactory::CreateInstance<IMHandler>(handler_type))
					{
						auto message = TypeFactory::CreateInstance<IMessage>(handler->GetRequestType());
						// 为这组件注册消息到达后的触发实例
						self->RegisterMessage(message->GetOpcode(), handler);
					}
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


