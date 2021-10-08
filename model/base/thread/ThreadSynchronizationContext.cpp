#include "ThreadSynchronizationContext.h"
#include "log/ServerLog.h"

namespace Model 
{
	ThreadSynchronizationContext* ThreadSynchronizationContext::Instance = nullptr;

	ThreadSynchronizationContext::ThreadSynchronizationContext()
	{
		m_thread_id = std::this_thread::get_id();

	}

	void ThreadSynchronizationContext::Update()
	{
		std::function<void()> task;
		while (!m_tasks.empty())
		{
			m_mutex.lock();
			task = std::move(m_tasks.front());
			m_tasks.pop();
			m_mutex.unlock();
			
			try {
				task();
			}
			catch (std::exception& e)
			{
				LOG_ERROR("执行主线程任务时，发生错误!({})", e.what());
			}
			catch (...)
			{
				LOG_ERROR("执行主线程任务时，发生错误!(未知错误)");
			}

		}
	}

	void ThreadSynchronizationContext::Post(std::function<void()>&& task)
	{
		if (std::this_thread::get_id() == m_thread_id)
		{
			// 在主线程中，直接执行任务
			try {
				task();
			}
			catch (std::exception& e)
			{
				LOG_ERROR("执行主线程任务时，发生错误!({})",e.what());
			}
			catch (...)
			{
				LOG_ERROR("执行主线程任务时，发生错误!(未知错误)");
			}
			return;
		}
		m_mutex.lock();
		m_tasks.emplace(std::move(task));
		m_mutex.unlock();
	}

	void ThreadSynchronizationContext::PostNext(std::function<void()>&& task)
	{
		m_mutex.lock();
		m_tasks.emplace(std::move(task));
		m_mutex.unlock();
	}
}