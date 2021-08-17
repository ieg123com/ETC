#pragma once
#include "other/string/str.h"
#include "etc_config.h"
#include "Object.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <set>
#include "IAwakeSystem.h"
#include "IloadSystem.h"
#include "IStartSystem.h"
#include "IUpdateSystem.h"
#include "ILateUpdateSystem.h"
#include "IDestroySystem.h"


namespace std
{
	template<typename _Ty1, typename _Ty2>
	struct hash<pair<_Ty1, _Ty2>>
	{
		size_t operator ()(const pair<_Ty1, _Ty2>& self) const noexcept {
			return hash<decltype(self.first)>()(self.first) +
				hash<decltype(self.second)>()(self.second);
		}
	};
}




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

	// 事件状态
	enum class EventCtxStatus : uint8_t
	{
		AddEvent,						// 添加事件
		DeleteAllEventInObject,			// 移除对象中的所有事件
		DeleteSpecificEventInObject,	// 移除对象中的指定事件
	};



	// 对象事件
	struct stObjectEventContext
	{
		EventCtxStatus	status;
		std::shared_ptr<Object> target_obj;
		std::shared_ptr<Object> self;
		std::string	event_id;

	};



	class MEventSystem
	{
		friend class ObjectDebug;
	public:
		MEventSystem();

		void Add(DLLType dll_type,std::shared_ptr<Reflection::Assembly> assembly);


		template<typename ...Arg>
		void Awake(const std::shared_ptr<Object>& self, Arg ...arg)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_awake_system.size() <= index)return;
			auto& all_obj = m_awake_system[index];
			for (auto& item : all_obj)
			{
				if (item->GetCallbackType() == typeid(void(Arg...)))
				{
					((IAwake<Arg...>*)(item.get()))->Run(self, arg...);
				}
			}
		}

		void Load(const std::shared_ptr<Object>& self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_load_system.size() <= index)return;
			auto& all_obj = m_load_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Start(const std::shared_ptr<Object>& self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_start_system.size() <= index)return;
			auto& all_obj = m_start_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Update(const std::shared_ptr<Object>& self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_update_system.size() <= index)return;
			auto& all_obj = m_update_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}
		
		void LateUpdate(const std::shared_ptr<Object>& self)
		{
			TypeIndex index = self->GetObjectType().GetTypeIndex();
			if (m_late_update_system.size() <= index)return;
			auto& all_obj = m_late_update_system[index];
			for (auto& item : all_obj)
			{
				item->Run(self);
			}
		}

		void Destroy(const std::shared_ptr<Object>& self)
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

		// 执行自定义事件
		template<typename ...Arg>
		void Run(const std::string& event_id, Arg...arg) {
			auto all_event_range = m_event_system.equal_range(event_id);
			while (all_event_range.first != all_event_range.second)
			{
				if (all_event_range.first->second->GetCallbackType() == typeid(void(Arg...)))
				{
					((IEvent<Arg...>*)(all_event_range.first->second.get()))->Handle(arg...);
				}
				++(all_event_range.first);
			}
		}

		// 执行自定义对象事件
		template<typename ...Arg>
		void Run(const std::shared_ptr<Object>& target_obj, const std::string& event_id, Arg...arg) {
			__ObjectEventOperationHandle();
			
			auto found_objevent = m_object_event.find(target_obj->GetObjectID());
			if (found_objevent == m_object_event.end())return;
			auto found_event_id = found_objevent->second.find(event_id);
			if (found_event_id == found_objevent->second.end())return;
			for (auto& item : found_event_id->second)
			{
				if (item.second.second->GetCallbackType() == typeid(void(Arg...)))
				{
					if (item.second.first->IsDisposed())
					{
						RemoveObjectEvent(target_obj, item.second.first, event_id);
					}
					else {
						((IObjEvent<Arg...>*)(item.second.second.get()))->Handle(item.second.first, arg...);
					}
				}

			}
		}


		void RegisterObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const std::string& event_id);

		void RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const std::string& event_id);
		void RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const std::string& event_id);
		void RemoveObjectEvent(const std::shared_ptr<Object>& target_obj);


	private:
		void __ObjectEventOperationHandle();
		void __AddEvent(const stObjectEventContext& ctx);
		void __DeleteAllEventInObject(const stObjectEventContext& ctx);
		void __DeleteSpecificEventInObject(const stObjectEventContext& ctx);
	private:

		std::unordered_map<DLLType, std::shared_ptr<Reflection::Assembly>>	m_assemblys;
		std::unordered_map<Type, std::set<Type>>			m_types;

		// 对象系统事件
		std::vector<std::list<std::shared_ptr<IAwakeSystem>>>		m_awake_system;
		std::vector<std::list<std::shared_ptr<ILoadSystem>>>		m_load_system;
		std::vector<std::list<std::shared_ptr<IStartSystem>>>		m_start_system;
		std::vector<std::list<std::shared_ptr<IUpdateSystem>>>		m_update_system;
		std::vector<std::list<std::shared_ptr<ILateUpdateSystem>>>	m_late_update_system;
		std::vector<std::list<std::shared_ptr<IDestroySystem>>>		m_destroy_system;

		// 自定义事件
		std::unordered_multimap<std::string, std::shared_ptr<IEventSystem>>	m_event_system;
		std::unordered_multimap<std::pair<std::string,Type>, std::shared_ptr<IObjEventSystem>>	m_objevent_system;

		using CObjectEventSystem = std::unordered_multimap<ObjectID,std::pair<std::shared_ptr<Object>, std::shared_ptr<IObjEventSystem>>>;
		// 自定义对象事件
		std::unordered_map<ObjectID, std::unordered_map<std::string,CObjectEventSystem>>	m_object_event;

		// 自定义对象事件待操作
		std::queue<stObjectEventContext>	m_object_event_operation;

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

