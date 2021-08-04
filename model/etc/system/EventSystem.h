#pragma once
#include "Object.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include "IAwakeSystem.h"
#include "IloadSystem.h"
#include "IStartSystem.h"
#include "IUpdateSystem.h"
#include "ILateUpdateSystem.h"
#include "IDestroySystem.h"



namespace Model
{
	namespace Reflection {
		class Assembly;
	}
	class Reflection::Assembly;


	enum class DLLType : uint8_t 
	{
		Model,
		Hotfix
	};


	class EventSystem
	{
	public:
		EventSystem();

		void Add(DLLType dll_type,std::shared_ptr<Reflection::Assembly> assembly);


		template<typename ...Arg>
		void Awake(std::shared_ptr<Object> self, Arg ...arg)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_awake_system.size() <= index)return;
			auto& all_obj = m_awake_system[index];
			for (auto& item : all_obj)
			{
				((IAwake<Arg...>*)item.get())->Run(self, arg...);
			}
		}

		void Load(std::shared_ptr<Object> self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_load_system.size() <= index)return;
			auto& all_obj = m_load_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Start(std::shared_ptr<Object> self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_start_system.size() <= index)return;
			auto& all_obj = m_start_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Update(std::shared_ptr<Object> self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_update_system.size() <= index)return;
			auto& all_obj = m_update_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}
		
		void LateUpdate(std::shared_ptr<Object> self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_late_update_system.size() <= index)return;
			auto& all_obj = m_late_update_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Destroy(std::shared_ptr<Object> self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_destroy_system.size() <= index)return;
			auto& all_obj = m_destroy_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		template<typename T>
		bool Exist(const std::vector<std::list<std::shared_ptr<T>>>& sys, const TypeIndex idx)
		{
			if (sys.size() <= idx)return false;
			if (sys[idx].empty())return false;
			return true;
		}

		template<typename T>
		void Add(std::vector<std::list<std::shared_ptr<T>>>& sys, const Type& t, std::shared_ptr<T> obj) {
			TypeIndex idx = t.m_info->index;
			if (sys.size() <= idx)
			{
				sys.resize(GlobalData::TypeIndex() + 1);
			}
			if (sys.size() <= idx) throw std::exception("TypeIndex 在 EventSystem 中出错");
			sys[idx].push_back(obj);
		}

	private:

		std::vector<std::list<std::shared_ptr<IAwakeSystem>>>		m_awake_system;
		std::vector<std::list<std::shared_ptr<ILoadSystem>>>		m_load_system;
		std::vector<std::list<std::shared_ptr<IStartSystem>>>		m_start_system;
		std::vector<std::list<std::shared_ptr<IUpdateSystem>>>		m_update_system;
		std::vector<std::list<std::shared_ptr<ILateUpdateSystem>>>	m_late_update_system;
		std::vector<std::list<std::shared_ptr<IDestroySystem>>>		m_destroy_system;

		std::unordered_map<DLLType, std::shared_ptr<Reflection::Assembly>>	m_assemblys;
		std::unordered_multimap<Type, Type>			m_types;

	public:

		void AddObject(const std::shared_ptr<Object>& obj);
		void RemoveObject(const std::shared_ptr<Object>& obj);
		std::shared_ptr<Object> GetObject(const ObjectID id) const;


		void Start();
		// 每帧更新
		void Update();
		// 最后更新
		void LateUpdate();

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

