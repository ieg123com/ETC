#pragma once
#include "etc/etc.h"
#include "coroutine.h"





// 地址组件，用来记录每个服务器中，id 对应的 instance id
class LocationComponent :
	public Component 
{
	
	// key: id	value: location id
	std::unordered_map<int64_t, int64_t>		m_key_location;
	// 每个 id 的锁
	std::unordered_map<int64_t, std::shared_ptr<co::CoMutex>>	m_key_lock;

public:
	static LocationComponent* Instance;

	void Add(const int64_t key, const int64_t instance_id);

	// 不是任何一个人就可以上锁的
	void Lock(const int64_t key, const int64_t instance_id ,const time_t time = 60000);

	void UnLock(const int64_t key, const int64_t old_instance_id, const int64_t new_instance_id);

	void Remove(const int64_t key);

	int64_t Get(const int64_t key);

	std::shared_ptr<co::CoMutex> GetMutex(const int64_t key);



};
