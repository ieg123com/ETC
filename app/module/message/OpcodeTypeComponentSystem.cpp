#include "model/module/message/OpcodeTypeComponent.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message.h"

class OpcodeTypeComponentAwakeSystem :public AwakeSystem<OpcodeTypeComponent>
{
public:
	virtual void Awake(const std::shared_ptr<OpcodeTypeComponent>& self) override
	{
		self->Awake();
	}
};
REF(OpcodeTypeComponentAwakeSystem, ObjectSystem);

class OpcodeTypeComponentLoadSystem :public LoadSystem<OpcodeTypeComponent>
{
public:
	virtual void Load(const std::shared_ptr<OpcodeTypeComponent>& self)override
	{
		OpcodeTypeComponent::Instance = self.get();

		self->Load();

		{
			
			// ע����Ϣ
			auto proto_message = Game::Event().GetAssemblysType<ProtoMessage>();
			for (auto& item : proto_message)
			{
				auto message = TypeFactory::CreateInstance<IMessage>(item.second->GetObjectType());

				self->__RegisterMessage(message->GetType(), message->GetOpcode(),message->GetMessageType());

				if (message->GetMessageType() == EMessageType::IActorMessage ||
					message->GetMessageType() == EMessageType::IActorLocationMessage)
				{
					// Ϊ ActorMessage ��Ĭ�ϻظ���Ϣ
					self->__BindRpcMessage(message->GetType(), typeof(ActorResponse));
				}
			}

			// ��Rpc��Ϣ��ͨ����Ϣ�ڲ�����
			auto mproto_message = Game::Event().GetAssemblysType<ProtoResponseMessage>();
			for (auto& item : mproto_message)
			{
				auto attr_type = item.second->GetObjectType();
				if (auto attr = std::dynamic_pointer_cast<ProtoResponseMessage>(item.second))
				{
					self->__BindRpcMessage(attr->GetObjectType(), attr->ResponseMessageType);
				}
			}
			
		}

	}
};
REF(OpcodeTypeComponentLoadSystem, ObjectSystem);

class OpcodeTypeComponentDestroySystem :public DestroySystem<OpcodeTypeComponent>
{
public:
	virtual void Destroy(const std::shared_ptr<OpcodeTypeComponent>& self)override
	{
		self->Destroy();
	}
};
REF(OpcodeTypeComponentDestroySystem, ObjectSystem);