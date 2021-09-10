#include "LocationComponent.h"


void LocationComponent::Add(const int64_t key, const int64_t instance_id)
{
	m_key_lock[key].lock();
	m_key_location[key] = instance_id;
	LOG_DEBUG("location add key: {}  instance id: {}",key,instance_id);
	m_key_lock[key].unlock();
}

void LocationComponent::Lock(const int64_t key, const int64_t instance_id, const time_t time)
{
	m_key_lock[key].lock();
	if (time > 0)
	{
		co_sleep(time);
		UnLock(key, instance_id, instance_id);
	}
}

void LocationComponent::UnLock(const int64_t key, const int64_t old_instance_id, const int64_t instance_id)
{

}

void LocationComponent::Remove(const int64_t key)
{

}

int64_t LocationComponent::Get(const int64_t key)
{

}