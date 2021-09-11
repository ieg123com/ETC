#include "ActorLocationSenderComponent.h"
#include "LocationProxyComponent.h"
#include "ActorLocationSender.h"




ActorLocationSenderComponent* ActorLocationSenderComponent::Instance = nullptr;


std::shared_ptr<ActorLocationSender> ActorLocationSenderComponent::GetOrCreate(const ID key)
{
	if (auto actor_location = GetChild<ActorLocationSender>(key))
	{
		return actor_location;
	}
	// 创建新的 ActorLocationSender
	return ObjectFactory::CreateWithHostAndId<ActorLocationSender>(Self(), key);
}

void ActorLocationSenderComponent::Remove(const ID key)
{
	if (auto actor_location = GetChild<ActorLocationSender>(key))
	{
		actor_location->Dispose();
	}
}


std::shared_ptr<IActorResponse> ActorLocationSenderComponent::__Call(const ID key, const std::shared_ptr<IActorRequest>& message)
{
	auto actor_location_sender = GetOrCreate(key);
	actor_location_sender->LastSendTime = Game::Time().NowServerMilliseconds();
	InstanceID instance_id = actor_location_sender->InstanceId();
	while (true)
	{
		if (actor_location_sender->ActorId == 0)
		{
			actor_location_sender->ActorId = LocationProxyComponent::Instance->Get(key);
			if (actor_location_sender->InstanceId() != instance_id)
			{
				// 获取 ActorLocation 期间，	sender 对象已经被销毁了
				throw rpc_exception(, "");
			}

		}


	}

}

