#include "model/module/actor/ActorMessageDispatcherComponent.h"


namespace Hotfix
{
	class ActorMessageDispatcherComponentAwakeSystem :public AwakeSystem<ActorMessageDispatcherComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<ActorMessageDispatcherComponent>& self)override
		{

		}
	};
	REF(ActorMessageDispatcherComponentAwakeSystem, ObjectSystem);

	class ActorMessageDispatcherComponentLoadSystem :public LoadSystem<ActorMessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ActorMessageDispatcherComponent>& self)override
		{
			ActorMessageDispatcherComponent::Instance = self.get();
		}
	};
	REF(ActorMessageDispatcherComponentLoadSystem, ObjectSystem);
}

