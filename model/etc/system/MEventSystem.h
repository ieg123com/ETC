#pragma once
#include "other/string/str.h"
#include "etc_config.h"
#include "Object.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include "IAwakeSystem.h"
#include "IloadSystem.h"
#include "IStartSystem.h"
#include "IUpdateSystem.h"
#include "ILateUpdateSystem.h"
#include "IDestroySystem.h"



#undef GetObject

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
		class IBaseAttribute;
	}


	enum class DLLType : uint8_t 
	{
		Model,
		Hotfix
	};

	// 事件状态
	enum class EventCtxStatus : uint8_t
	{
		AddEvent,						// 添加事件
		DeleteSpecificEventInObject,	// 移除对象中的指定事件
	};



	// 对象事件
	struct stObjectEventContext
	{
		EventCtxStatus	status;
		// 事件会添加到这个对象身上
		std::shared_ptr<Object> self;
		InstanceID	self_instanceid;
		// 发起注册的对象，事件触发后会传递这个对象到事件实例
		std::shared_ptr<Object> reg_obj;
		InstanceID	reg_obj_instanceid;
		uint32_t	event_id;

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
			bool have_action = false;
			for (auto& item : all_obj)
			{
				if (item->GetCallbackType() == to_typeindex<void(Arg...)>())
				{
					have_action = true;
					((IAwake<Arg...>*)(item.get()))->Run(self, arg...);
				}
			}
			if(!all_obj.empty() && !have_action){
				LOG_WARN("{} not found Awake '{}'", self->GetObjectType().GetName(), typeof(IAwake<Arg...>).full_name());
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
		bool Exist(const std::vector<T>& sys, const TypeIndex idx)
		{
			if (sys.size() <= idx)return false;
			if (sys[idx].empty())return false;
			return true;
		}

		// 取出一个值的引用，如果vector长度不够，将自动扩容1.5倍。
		template<typename T>
		T& GetOrCreate(std::vector<T>& vec, const size_t index) {
			if (vec.size() <= index)
			{
				// vector 长度不够
				vec.resize((index+1) * 1.5f);
			}
			return vec[index];
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
		void Publish(Arg...arg) {
			auto &all_event = GetOrCreate(m_event_system, to_eventindex<Arg...>());
			for (auto& action : all_event)
			{
				((IEvent<Arg...>*)(action.get()))->Handle(arg...);
			}
		}

		// 执行自定义对象事件
		template<typename ...Arg>
		void Publish(const std::shared_ptr<Object>& target_obj, Arg...arg) {
			__ObjectEventOperationHandle();
			auto& all_event = GetOrCreate(m_object_event, to_eventindex<Arg...>()).find(target_obj->InstanceId());
			for (auto& action : all_event->second)
			{
				((IObjEvent<Arg...>*)(action.second.second.get()))->Handle(action.second.first, arg...);
			}
		}

		/**
		 * @brief	注册 对象事件
		 * @param [in] self		挂载事件的对象，如 m_host 或 自己
		 * @param [in] reg_obj	注册这个事件的对象。事件触发时，会将这个对象传过去
		 * @attention	这个函数需要放到 LoadSystem 中调用，必须在 DestroySystem 中移除。
		 * @code
		 * RegisterObjectEvent<EventType::Hit&>(self->host,self);
		 * @endcode
		 */
		template<typename ...Arg>
		void RegisterObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj) {
			RegisterObjectEvent(self, reg_obj, to_eventindex<Arg...>());
		}

		void RegisterObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj, const uint32_t event_id);

		/**
		 * @brief	注册 对象事件
		 * @param [in] self		挂载事件的对象，注册时填写的对象。
		 * @param [in] reg_obj	注册这个事件的对象。注册时填写的对象。
		 * @code
		 * RemoveObjectEvent<EventType::Hit&>(self->host,self);
		 * @endcode
		 */
		template<typename T>
		void RemoveObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj){
			RemoveObjectEvent(self, reg_obj, to_eventindex<Arg...>());
		}

		void RemoveObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj, const uint32_t event_id);


		const std::unordered_map<DLLType, std::shared_ptr<Reflection::Assembly>>& GetAssemblys()const { return m_assemblys; };

		/** 
		 * @brief	获取这个特性的全部实例
		 * @return	key: ObjectType  value: AttributeInstance
		 */
		template<typename T>
		std::unordered_map<Type, std::shared_ptr<Reflection::IBaseAttribute>> GetAssemblysType() {
			return std::move(GetAssemblysType(typeof(T)));
		}

		std::unordered_map<Type, std::shared_ptr<Reflection::IBaseAttribute>> GetAssemblysType(const Type& tp)const;


	private:
		// 记录每个模组内部用到的反射对象
		std::unordered_map<DLLType, std::shared_ptr<Reflection::Assembly>>	m_assemblys;
		// 所有反射的类型
		std::unordered_map<Type, std::set<Type>>			m_types;



		// 对象系统事件
		std::vector<std::list<std::shared_ptr<IAwakeSystem>>>		m_awake_system;
		std::vector<std::list<std::shared_ptr<ILoadSystem>>>		m_load_system;
		std::vector<std::list<std::shared_ptr<IStartSystem>>>		m_start_system;
		std::vector<std::list<std::shared_ptr<IUpdateSystem>>>		m_update_system;
		std::vector<std::list<std::shared_ptr<ILateUpdateSystem>>>	m_late_update_system;
		std::vector<std::list<std::shared_ptr<IDestroySystem>>>		m_destroy_system;


	public:

		// 获取事件类型的索引,没有的将会自动生成新的索引
		uint32_t GetOrGenEventIndex(const Type& tp);
		
		template<typename ...Arg>
		uint32_t to_eventindex() {
			static uint32_t event_id = GetOrGenEventIndex(typeof(void(Arg...)));
			return event_id;
		}


	private:
		void __ObjectEventOperationHandle();
		void __AddEvent(const stObjectEventContext& ctx);
		// 删除挂在这对象上的全部事件
		void __DeleteSpecificEventInObject(const InstanceID self_instanceid, const InstanceID reg_obj_instanceid, const uint32_t event_id,const bool cache_clear = true);

	private:


		// 自定义事件
		// index: event id  values: event instance
		std::vector<std::list<std::shared_ptr<IEventSystem>>>		m_event_system;
		// 这里是从反射获取的对象事件，先储存起来，有注册函数调用
		// index: event id  value: <key: reg_obj type  value: event instance>
		std::vector<std::unordered_multimap<Type, std::shared_ptr<IObjEventSystem>>>	m_objevent_system;

		// 对象回调实例
		// key: 注册的对象instance id  value: <key: 注册的对象实例  value: 事件实例>
		using CObjectEventSystem = std::unordered_multimap<InstanceID, std::pair<std::shared_ptr<Object>, std::shared_ptr<IObjEventSystem>>>;
		// 自定义对象事件
		// key: 事件挂载对象instance id  value: 注册对象回调实例
		std::vector<std::unordered_map<InstanceID, CObjectEventSystem>>	m_object_event;

		// 自定义对象事件待操作
		std::queue<stObjectEventContext>	m_object_event_operate;


		std::unordered_map<Type, uint32_t>	m_eventtype_to_index;

	public:

		void AddObject(const std::shared_ptr<Object>& obj);
		void RemoveObject(const std::shared_ptr<Object>& obj);
		std::shared_ptr<Object> GetObject(const InstanceID id) const;


		void Start();
		// 每帧更新
		void Update();
		// 最后更新
		void LateUpdate();

	private:
		std::unordered_map<InstanceID, std::shared_ptr<Object>> m_objects;


		std::unordered_map<InstanceID, std::shared_ptr<Object>> m_updates;
		std::unordered_map<InstanceID, std::shared_ptr<Object>> m_late_updates;

		std::queue<std::shared_ptr<Object>>	m_start_enter;
	private:
		std::queue<InstanceID>	m_update_enter;
		std::queue<InstanceID>	m_update_leave;

		std::queue<InstanceID>	m_late_update_enter;
		std::queue<InstanceID>	m_late_update_leave;

	};
}

