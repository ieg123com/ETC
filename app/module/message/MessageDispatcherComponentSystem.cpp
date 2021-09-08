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
				// ��ָ����Ϣidע��ص�ʵ��
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
					if (auto handler = TypeFactory::CreateInstance<IMHandler>(handler_type))
					{
						auto message = TypeFactory::CreateInstance<IMessage>(handler->GetRequestType());
						// Ϊ�����ע����Ϣ�����Ĵ���ʵ��
						self->RegisterMessage(message->GetOpcode(), handler);
					}
				}
			}
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


