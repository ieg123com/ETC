#pragma once
#include <list>
#include <memory>
#include "task.h"
#include "single/ISingleton.h"



namespace Model
{
	class DomainTask:
		public IDomainSingleton<DomainTask>
	{
	public:


		template<typename T>
		void Add(T&& task) {
			Task* new_task = new Task();
			new_task->Bind(task);
			m_tasks.push_back(new_task);
		}

		void RunAll() {
			auto iter = m_tasks.begin();
			while (iter != m_tasks.end())
			{
				(*iter)->Run();
				delete (*iter);
				iter = m_tasks.erase(iter);
			}
		}

	private:
		std::list<Task*> m_tasks;
	};

	

	class AddDomainTask
	{
	public:
		AddDomainTask(std::function<void()>&& task) {
			printf("AddDomainTask\n");
			DomainTask::Instance().Add(task);
		}
	};

	


}