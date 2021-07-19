#pragma once
#include "Object.h"
#include <unordered_map>
#include <queue>
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


		template<typename ...Arg>
		void Awake(std::shared_ptr<Object> self, Arg ...arg)
		{
			auto found = m_awake_system.equal_range(self->GetObjectType().m_type);
			while (found.first != found.second)
			{
				((IAwake<Arg...>*)found.first->second)->Run(self, arg...);
			}
		}

		void Start(std::shared_ptr<Object> self)
		{
			auto found = m_start_system.equal_range(self->GetObjectType().m_type);
			while (found.first != found.second)
			{
				found.first->second->Run(self);
			}
		}

		void Update(std::shared_ptr<Object> self)
		{
			auto found = m_update_system.equal_range(self->GetObjectType().m_type);
			while (found.first != found.second)
			{
				found.first->second->Run(self);
			}
		}
		
		void LateUpdate(std::shared_ptr<Object> self)
		{
			auto found = m_late_update_system.equal_range(self->GetObjectType().m_type);
			while (found.first != found.second)
			{
				found.first->second->Run(self);
			}
		}

		void Destroy(std::shared_ptr<Object> self)
		{
			auto found = m_destroy_system.equal_range(self->GetObjectType().m_type);
			while (found.first != found.second)
			{
				found.first->second->Run(self);
			}
		}

	private:

		std::unordered_multimap<Type, IAwakeSystem*>		m_awake_system;
		std::unordered_multimap<Type, IStartSystem*>		m_start_system;
		std::unordered_multimap<Type, IUpdateSystem*>		m_update_system;
		std::unordered_multimap<Type, ILateUpdateSystem*>	m_late_update_system;
		std::unordered_multimap<Type, IDestroySystem*>		m_destroy_system;


	public:

		void AddObject(const std::shared_ptr<Object>& obj);
		void RemoveObject(const std::shared_ptr<Object>& obj);
		std::shared_ptr<Object> GetObject(const ObjectID id) const;




	private:
		std::unordered_map<ObjectID, std::shared_ptr<Object>> m_objects;


		std::unordered_map<ObjectID, std::shared_ptr<Object>> m_updates;
		std::unordered_map<ObjectID, std::shared_ptr<Object>> m_late_updates;

		std::queue<std::shared_ptr<Object>>	m_start_enter;
	private:
		std::queue<ObjectID>	m_update_enter;
		std::queue<ObjectID>	m_update_leave;

		std::queue<ObjectID>	m_late_update_enter;
		std::queue<ObjectID>	m_late_update_leave;


	};
}

