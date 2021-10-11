#include "scheduler.h"
#include "other/string/str.h"

namespace Model
{
	namespace async
	{
		Scheduler* Scheduler::Instance = nullptr;
		Scheduler::Scheduler()
		{
			m_stop = false;
			m_thread_num = 10;
		}

		Scheduler::~Scheduler()
		{
			Stop();
		}

		void Scheduler::Push(const std::shared_ptr<BaseTask>& task)
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				if (m_stop)return;
				if (!m_taskid.emplace(task->__Id, task).second)
					throw std::exception(std::format("Push the same task repeatedly,id = %lld\n", task->__Id).c_str());
				m_tasks.push(task);
				task->__State = TaskState::Pending;
			}
			m_condition.notify_one();
		}

		void Scheduler::Start(const size_t thread_num)
		{
			m_thread_num = thread_num;
			for (int i = 0; i < m_thread_num; ++i)
			{
				m_threads.emplace_back(new std::thread([this] {
					std::shared_ptr<BaseTask> task;
					for (;;)
					{
						{
							std::unique_lock<std::mutex> lock(m_mutex);
							m_condition.wait(lock,
								[this] {return (this->m_stop || !this->m_tasks.empty()); });
							if (this->m_stop && this->m_tasks.empty())break;	// 这个线程可以停止了
							task = std::move(m_tasks.front());
							m_tasks.pop();
							m_taskid.erase(task->__Id);
						}
						if (task->__State == TaskState::Pending)
						{
							// 可以执行这任务
							task->run();
						}
					}
					printf("thread stop...\n");
					// 线程结束...
					}));
			}
		}

		void Scheduler::Stop()
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				if (m_stop)return;
				m_stop = true;
			}
			m_condition.notify_all();
			for (auto td : m_threads)
			{
				td->join();
				delete td;
			}
			m_threads.clear();

		}

	}
}