#include "LocationComponent.h"




void LocationComponent::Add(const ID key, const InstanceID instance_id)
{
	auto lock = GetMutex(key);
	lock->lock();
	m_key_location[key] = instance_id;
	LOG_DEBUG("location add key: {}  instance id: {}",key,instance_id);
	lock->unlock();
}

void LocationComponent::Lock(const ID key, const InstanceID instance_id, const time_t time)
{
	auto lock = GetMutex(key);
	lock->lock();
	LOG_DEBUG("location lock key: {}  new location id: {}  time: {}", key, instance_id,time);
	if (time > 0)
	{
		co_sleep(time);
		UnLock(key, instance_id, instance_id);
	}
}

void LocationComponent::UnLock(const ID key, const InstanceID old_instance_id, const InstanceID new_instance_id)
{
	if (m_key_location[key] != old_instance_id)
		return;
	LOG_DEBUG("location unlock key: {}  new location id: {}", key, new_instance_id);
	auto lock = GetMutex(key);
	m_key_location[key] = new_instance_id;
	if (lock->is_lock())
	{
		lock->unlock();
	}

}

void LocationComponent::Remove(const ID key)
{
	auto lock = GetMutex(key);
	lock->lock();
	m_key_location.erase(key);
	m_key_lock.erase(key);
	LOG_DEBUG("location remove key: {}", key);
	lock->unlock();
}

int64_t LocationComponent::Get(const ID key)
{
	auto lock = GetMutex(key);
	lock->lock();
	InstanceID instance_id = m_key_location[key];
	LOG_DEBUG("location get key: {}  location id: {}", key, instance_id);
	lock->unlock();
	return instance_id;
}

std::shared_ptr<co::CoMutex> LocationComponent::GetMutex(const ID key)
{
	auto found = m_key_lock.find(key);
	if (found == m_key_lock.end())
	{
		return m_key_lock.emplace(key, std::make_shared<co::CoMutex>()).first->second;
	}
	return found->second;
}