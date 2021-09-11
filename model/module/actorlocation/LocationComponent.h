#pragma once
#include "etc/etc.h"
#include "coroutine.h"





// 地址组件，用来记录每个服务器中，id 对应的 instance id
class LocationComponent :
	public Component 
{
	
	// key: id	value: location id
	std::unordered_map<ID, InstanceID>		m_key_location;
	// 每个 id 的锁
	std::unordered_map<ID, std::shared_ptr<co::CoMutex>>	m_key_lock;

public:

	void Add(const ID key, const InstanceID instance_id);

	void Lock(const ID key, const InstanceID instance_id ,const time_t time = 60000);

	void UnLock(const ID key, const InstanceID old_instance_id, const InstanceID new_instance_id);

	void Remove(const ID key);

	int64_t Get(const ID key);

	std::shared_ptr<co::CoMutex> GetMutex(const ID key);



};
