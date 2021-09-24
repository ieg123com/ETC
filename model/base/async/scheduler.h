#pragma once
#include "task.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

namespace Model
{
	namespace async
	{
		class Scheduler
		{
		public:
			static Scheduler* Instance;

			Scheduler();
			~Scheduler();

			void Push(const std::shared_ptr<BaseTask>& task);

			/**
			* @brief	开始线程池
			* @param[in] thread_num : 线程数
			*/
			void Start(const size_t thread_num = 2);

			void Stop();

		private:
			size_t	m_thread_num;
			std::vector<std::thread*>	m_threads;
			std::queue<std::shared_ptr<BaseTask>>	m_tasks;
			std::unordered_map<int64_t, std::shared_ptr<BaseTask>>	m_taskid;


			std::condition_variable	m_condition;
			std::mutex	m_mutex;
			bool m_stop;


		};

	}
}