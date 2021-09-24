#pragma once
#include "scheduler.h"

namespace Model
{
	namespace async
	{

		class Async
		{
		public:
			template<typename T>
			inline std::result_of_t<std::decay_t<T>()>
				operator - (T&& cb)const {
				auto task = std::make_shared<Task<std::result_of_t<std::decay_t<T>()>>>();
				task->__SetTask(cb);
				Scheduler::Instance->Push(task);
				while (task->wait(std::chrono::seconds(1)) == false){}
				if (task->canceled())
					throw std::exception(task->exception().c_str());
				return task->get();
			}

		};

	}
}

#define await	::Model::async::Async() -