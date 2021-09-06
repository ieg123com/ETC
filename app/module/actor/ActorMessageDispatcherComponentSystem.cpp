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
				// Ϊ Actor ��Ϣע��ص�ʵ��
				auto appTyep = Game::Options().AppType;
				auto proto_message = Game::Event().GetAssemblysType<Message>();
				for (auto& item : proto_message)
				{
					// ����һ������ʵ��
					auto attr = std::dynamic_pointer_cast<Message>(item.second);
					// ��鴥�����Ƿ�֧�ֵ�ǰ����
					if (!Is((EAppType)attr->appType, appTyep))continue;
					// ��Ϣ����������͡�����ȡ���������ʵ����װ�Ķ������ͣ�
					Type handler_type = attr->GetObjectType();
					// ��Ϣ�������ʵ��
					auto handler = TypeFactory::CreateInstance<IMSystemHandler>(handler_type);
					auto message = TypeFactory::CreateInstance<IMessage>(handler->GetRequestType());
					// Ϊ�����ע����Ϣ�����Ĵ���ʵ��
					self->RegisterMessage(message->GetOpcode(), handler);
				}
			}
		}
	};
	REF(ActorMessageDispatcherComponentLoadSystem, ObjectSystem);
}

