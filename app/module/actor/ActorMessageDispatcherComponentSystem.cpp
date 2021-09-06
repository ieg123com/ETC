#include "model/module/actor/ActorMessageDispatcherComponent.h"


namespace Hotfix
{
	class ActorMessageDispatcherComponentAwakeSystem :public AwakeSystem<ActorMessageDispatcherComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<ActorMessageDispatcherComponent>& self)override
		{
			self->Awake();
		}
	};
	REF(ActorMessageDispatcherComponentAwakeSystem, ObjectSystem);

	class ActorMessageDispatcherComponentLoadSystem :public LoadSystem<ActorMessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ActorMessageDispatcherComponent>& self)override
		{
			ActorMessageDispatcherComponent::Instance = self.get();
			self->Clear();

			{
				// 为 Actor 消息注册回调实例
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
					auto handler = TypeFactory::CreateInstance<IMSystemHandler>(handler_type);
					auto message = TypeFactory::CreateInstance<IMessage>(handler->GetRequestType());
					// 为这组件注册消息到达后的触发实例
					self->RegisterMessage(message->GetOpcode(), handler);
				}
			}
		}
	};
	REF(ActorMessageDispatcherComponentLoadSystem, ObjectSystem);
}

