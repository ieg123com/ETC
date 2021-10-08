#pragma once
#include <queue>
#include <mutex>
#include <functional>


namespace Model
{
	// �߳�ͬ�������Ĵ���
	// ���Խ������߳��е����񣬷ŵ�ָ���߳���ִ�С�
	class ThreadSynchronizationContext
	{
		std::queue<std::function<void()>>	m_tasks;
		std::thread::id	m_thread_id;	// ���߳�id
		std::mutex	m_mutex;
	public:
		static ThreadSynchronizationContext* Instance;


		void Update();
		void Post(std::function<void()>&& task);
		void PostNext(std::function<void()>&& task);
	};


}

