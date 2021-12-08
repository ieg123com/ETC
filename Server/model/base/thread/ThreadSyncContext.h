#pragma once
#include <queue>
#include <mutex>
#include <functional>


namespace Model
{
	// 线程同步上下文处理
	// 可以将其他线程中的任务，放到指定线程中执行。
	class ThreadSyncContext
	{
		std::queue<std::function<void()>>	m_tasks;
		std::thread::id	m_thread_id;	// 主线程id
		std::mutex	m_mutex;
	public:
		static ThreadSyncContext* Instance;

		ThreadSyncContext();

		void Update();
		void Post(std::function<void()>&& task);
		void PostNext(std::function<void()>&& task);
	};


}
