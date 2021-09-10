#pragma once
#include "etc/etc.h"
#include "CoroutineLock.h"
#include <map>


// 用于管理协程锁，防止死锁
class CoroutineLockComponent :
	public Component
{
	// 所有协程锁
	// key: id  value: lock
	std::unordered_map<int64_t, std::shared_ptr<CoroutineLock>>	m_coroutine_locks;

	// 协程锁的超时时间
	// key: timeout  value: id
	std::map<time_t, int64_t>		m_timeid;

	// 超时需要解锁的id
	std::queue<int64_t>		m_timeout_id;
public:
	static CoroutineLockComponent* Instance;

	// 检查超时的锁，自动解开。防止死锁
	void Check();


	void Lock();



private:

	







};


