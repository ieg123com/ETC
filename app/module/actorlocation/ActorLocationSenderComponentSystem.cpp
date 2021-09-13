#include "model/module/actorlocation/ActorLocationSenderComponent.h"
#include "ActorLocationSenderComponentHandler.h"





namespace Hotfix
{


	class ActorLocationSenderComponentAwakeSystem :public AwakeSystem<ActorLocationSenderComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<ActorLocationSenderComponent>& self)override
		{
			self->CheckTimer = TimerComponent::Instance->RegisterRepeatedTimer(10 * 1000, [=] {ActorLocationSenderComponentHandler::Check(self); });
		}
	};
	REF(ActorLocationSenderComponentAwakeSystem, ObjectSystem);


	class ActorLocationSenderComponentLoadSystem :public LoadSystem<ActorLocationSenderComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ActorLocationSenderComponent>& self)override
		{
			ActorLocationSenderComponent::Instance = self.get();
		}

	};
	REF(ActorLocationSenderComponentLoadSystem, ObjectSystem);

	class ActorLocationSenderComponentDestroySystem :public DestroySystem<ActorLocationSenderComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<ActorLocationSenderComponent>& self)override
		{
			TimerComponent::Instance->RemoveTimer(self->CheckTimer);
		}
	};
	REF(ActorLocationSenderComponentDestroySystem, ObjectSystem);

}