#include "model/module/actor/ActorMessageSenderComponent.h"


class ActorMessageSenderComponentAwakeSystem :public AwakeSystem<ActorMessageSenderComponent>
{
public:
	virtual void Awake(const std::shared_ptr<ActorMessageSenderComponent>& self)override
	{
		self->Awake();
	}
};
REF(ActorMessageSenderComponentAwakeSystem, ObjectSystem);

class ActorMessageSenderComponentLoadSystem :public LoadSystem<ActorMessageSenderComponent>
{
public:
	virtual void Load(const std::shared_ptr<ActorMessageSenderComponent>& self)override
	{
		ActorMessageSenderComponent::Instance = self.get();
	}
};
REF(ActorMessageSenderComponentLoadSystem, ObjectSystem);

class ActorMessageSenderComponentDestroySystem :public DestroySystem<ActorMessageSenderComponent>
{
public:
	virtual void Destroy(const std::shared_ptr<ActorMessageSenderComponent>& self)override
	{
		self->Destory();
	}
};
REF(ActorMessageSenderComponentDestroySystem, ObjectSystem);