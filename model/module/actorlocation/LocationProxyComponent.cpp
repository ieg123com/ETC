#include "LocationProxyComponent.h"
#include "module/actor/ActorMessageSenderComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "proto/EtcMsg.pb.h"



void LocationProxyComponent::Add(const int64_t key, const int64_t instance_id)
{
	auto request = std::make_shared<A2L_ObjectAddRequest>();
	request->set_key(key);
	request->set_instanceid(instance_id);
	ActorMessageSenderComponent::Instance->Call(GetLocationAppId(key), request);
}

void LocationProxyComponent::Lock(const int64_t key, const int64_t instance_id, const int32_t time)
{
	auto request = std::make_shared<A2L_ObjectLockRequest>();
	request->set_key(key);
	request->set_instanceid(instance_id);
	request->set_time(time);
	ActorMessageSenderComponent::Instance->Call(GetLocationAppId(key), request);
}

void LocationProxyComponent::UnLock(const int64_t key, const int64_t old_instance_id, const int64_t instance_id)
{
	auto request = std::make_shared<A2L_ObjectUnLockRequest>();
	request->set_key(key);
	request->set_oldinstanceid(old_instance_id);
	request->set_instanceid(instance_id);
	ActorMessageSenderComponent::Instance->Call(GetLocationAppId(key), request);
}

void LocationProxyComponent::Remove(const int64_t key)
{
	auto request = std::make_shared<A2L_ObjectRemoveRequest>();
	request->set_key(key);
	ActorMessageSenderComponent::Instance->Call(GetLocationAppId(key), request);
}

int64_t LocationProxyComponent::Get(const int64_t key)
{
	if (key == 0)
	{
		throw std::exception("get location key : 0");
	}
	auto request = std::make_shared<A2L_ObjectGetRequest>();
	request->set_key(key);
	auto resqouse = ActorMessageSenderComponent::Instance->Call<L2A_ObjectGetResponse>(GetLocationAppId(key), request);
	return resqouse->instanceid();
}

InstanceID LocationProxyComponent::GetLocationAppId(const int64_t key)
{
	return StartConfigComponent::Instance->LocationConfig->InstanceId;
}