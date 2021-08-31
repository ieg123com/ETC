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
			// TODO:  绑定已注册的类型
			auto& message_system = Game::Event().__message_system;
			for (auto& item : message_system)
			{
				if (auto msg_instance = std::dynamic_pointer_cast<IRpcMessageSystem>(item))
				{
					self->BindRpcMessage(msg_instance->GetRequestType(), msg_instance->GetResponseType());
				}
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