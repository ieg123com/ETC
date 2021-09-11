#include "model/module/actorlocation/ActorLocationSenderComponent.h"




namespace Hotfix
{


	class ActorLocationSenderComponentAwakeSystem :public AwakeSystem<ActorLocationSenderComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<ActorLocationSenderComponent>& self)override
		{

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

}