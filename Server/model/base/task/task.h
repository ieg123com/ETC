#pragma once
#include <functional>



namespace Model
{


	class Task
	{
	public:
		Task() {}
		Task(const std::function<void()>& task) {
			m_task = task;
		}

		template<typename T>
		void Bind(T&& task) {
			m_task = std::move(task);
		}

		void Run() {
			m_task();
		}

	private:
		std::function<void()>	m_task;
	};
}