#pragma once
#include "Object.h"
#include <unordered_map>
#include "IAwakeSystem.h"
#include "IStartSystem.h"
#include "IUpdateSystem.h"
#include "ILateUpdateSystem.h"
#include "IDestroySystem.h"



namespace Model
{

	class EventSystem
	{
	public:
		EventSystem();


		template<typename T,typename ...Arg>
		void Awake(std::shared_ptr<T> self, Arg ...arg)
		{
			auto found = m_awake_system.equal_range(typeof(self));
			while (found.first != found.second)
			{
				((AwakeSystem<T, Arg...>*)found.first->second)->Run(self, arg...);
			}
		}

		template<typename T>
		void Start(std::shared_ptr<T> self)
		{
			auto found = m_start_system.equal_range(typeof(self));
			while (found.first != found.second)
			{
				((StartSystem<T>*)found.first->second)->Run(self);
			}
		}

		template<typename T>
		void Update(std::shared_ptr<T> self)
		{
			auto found = m_update_system.equal_range(typeof(self));
			while (found.first != found.second)
			{
				((UpdateSystem<T>*)found.first->second)->Run(self);
			}
		}
		
		template<typename T>
		void LateUpdate(std::shared_ptr<T> self)
		{
			auto found = m_late_update_system.equal_range(typeof(self));
			while (found.first != found.second)
			{
				((LateUpdateSystem<T>*)found.first->second)->Run(self);
			}
		}

		template<typename T>
		void Destroy(std::shared_ptr<T> self)
		{
			auto found = m_destroy_system.equal_range(typeof(self));
			while (found.first != found.second)
			{
				((DestroySystem<T>*)found.first->second)->Run(self);
			}
		}

	private:

		std::unordered_multimap<Type, IAwakeSystem*>		m_awake_system;
		std::unordered_multimap<Type, IStartSystem*>		m_start_system;
		std::unordered_multimap<Type, IUpdateSystem*>		m_update_system;
		std::unordered_multimap<Type, ILateUpdateSystem*>	m_late_update_system;
		std::unordered_multimap<Type, IDestroySystem*>		m_destroy_system;



	};
}

