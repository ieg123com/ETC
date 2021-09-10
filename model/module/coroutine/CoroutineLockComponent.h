#pragma once
#include "etc/etc.h"
#include "CoroutineLock.h"
#include <map>


// ���ڹ���Э��������ֹ����
class CoroutineLockComponent :
	public Component
{
	// ����Э����
	// key: id  value: lock
	std::unordered_map<int64_t, std::shared_ptr<CoroutineLock>>	m_coroutine_locks;

	// Э�����ĳ�ʱʱ��
	// key: timeout  value: id
	std::map<time_t, int64_t>		m_timeid;

	// ��ʱ��Ҫ������id
	std::queue<int64_t>		m_timeout_id;
public:
	static CoroutineLockComponent* Instance;

	// ��鳬ʱ�������Զ��⿪����ֹ����
	void Check();


	void Lock();



private:

	







};


