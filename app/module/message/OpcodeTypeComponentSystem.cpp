#include "model/module/message/OpcodeTypeComponent.h"
#include "model/module/other/SystemEventType.h"


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
			// TODO:  ×¢²áÏûÏ¢
			auto& message_system = Game::Event().GetAssemblysType<ProtoMessage>();
			for (auto& item : message_system)
			{
				auto attr_type = item.second->GetObjectType();
				auto message = TypeFactory::CreateInstance<IMessage>(attr_type);

				self->__RegisterMessage(message->GetType(), message->GetOpcode(),message->GetMessageType());
			}
		}

		Game::Event().Run<const std::shared_ptr<OpcodeTypeComponent>&>(ESystemEventType::StartBindRpcMessage, self);

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