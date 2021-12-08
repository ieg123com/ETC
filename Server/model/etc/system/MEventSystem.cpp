#include "MEventSystem.h"
#include "Game.h"
#include "reflection/reflection.h"
#include "interface/ObjectSystemAttribute.h"
#include "interface/EventSystemAttribute.h"
#include "module/message/interface/MessageSystemAttribute.h"

namespace Model
{


	MEventSystem::MEventSystem()
	{
	}


	void MEventSystem::Add(DLLType dll_type, std::shared_ptr<Reflection::Assembly> assembly)
	{
		m_assemblys[dll_type] = assembly;
		m_types.clear();
		for (auto& item : m_assemblys)
		{
			auto all_attr = item.second->GetType<ObjectSystem>();
			for (auto& attr : all_attr)
			{
				if (m_types[attr->GetAttrType()].insert(attr->GetObjectType()).second)
				{
					LOG_WARN("object type {}:{}", attr->GetObjectType().name(),attr->GetObjectType().m_info->index);
				}
			}
		}

		// 默认对象系统事件
		m_awake_system.clear();
		m_load_system.clear();
		m_start_system.clear();
		m_update_system.clear();
		m_late_update_system.clear();
		m_destroy_system.clear();

		auto os_attr = m_types.find(typeof(ObjectSystem));
		if (os_attr != m_types.end())
		{
			for (auto& attr : os_attr->second)
			{
				auto obj = TypeFactory::CreateInstance<IEventSystem>(attr);
				if (!obj)
					LOG_WARN("System event 创建类型失败，请检测继承是否为'public'，type = {}:{}", attr.full_name(), attr.m_info->index);

				if (auto sys = std::dynamic_pointer_cast<IAwakeSystem>(obj))
				{
					Add(m_awake_system, obj->GetType(), sys);
				}
				else if (auto sys = std::dynamic_pointer_cast<ILoadSystem>(obj))
				{
					Add(m_load_system, obj->GetType(), sys);
				}
				else if (auto sys = std::dynamic_pointer_cast<IStartSystem>(obj))
				{
					Add(m_start_system, obj->GetType(), sys);
				}
				else if (auto sys = std::dynamic_pointer_cast<IUpdateSystem>(obj))
				{
					Add(m_update_system, obj->GetType(), sys);
				}
				else if (auto sys = std::dynamic_pointer_cast<ILateUpdateSystem>(obj))
				{
					Add(m_late_update_system, obj->GetType(), sys);
				}
				else if (auto sys = std::dynamic_pointer_cast<IDestroySystem>(obj))
				{
					Add(m_destroy_system, obj->GetType(), sys);
				}
			}
		}


		// 自定义事件
		{
			m_event_system.clear();
			m_objevent_system.clear();

			auto all_event_attr = GetAssemblysType<Event>();
			for (auto& event_attr : all_event_attr)
			{
				auto event_obj = TypeFactory::CreateInstance<IEventSystem>(event_attr.first);
				uint32_t event_id = GetOrGenEventIndex(to_type(event_obj->GetCallbackType()));
				if (auto instance = std::dynamic_pointer_cast<IObjEventSystem>(event_obj))
				{
					// 对象事件
					GetOrCreate(m_objevent_system, event_id).emplace(instance->GetType(), instance);
				}
				else {
					// 普通事件
					GetOrCreate(m_event_system, event_id).push_back(event_obj);
				}
			}

		}


		{
			// 自定义对象事件清除
			m_object_event.clear();
			while(!m_object_event_operate.empty())m_object_event_operate.pop();
			
			for (auto& item : m_objects)
			{
				Load(item.second);
			}
		}

	}

	void MEventSystem::RegisterObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj, const uint32_t event_id) {
		static stObjectEventContext ctx;
		if (!self) throw std::exception("target_obj cannot be null");
		if (!reg_obj) throw std::exception("self cannot be null");
		if (event_id == 0) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::AddEvent;
		ctx.self = self;
		ctx.reg_obj = reg_obj;
		ctx.event_id = event_id;
		m_object_event_operate.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& self, const std::shared_ptr<Object>& reg_obj, const uint32_t event_id)
	{
		static stObjectEventContext ctx;
		if (!self) throw std::exception("target_obj cannot be null");
		if (!reg_obj) throw std::exception("self cannot be null");
		if (event_id == 0) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::DeleteSpecificEventInObject;
		ctx.self = self;
		ctx.reg_obj = reg_obj;
		ctx.event_id = event_id;
		m_object_event_operate.emplace(std::move(ctx));
	}


	std::unordered_map<Type, std::shared_ptr<Reflection::IBaseAttribute>> MEventSystem::GetAssemblysType(const Type& tp)const
	{
		std::unordered_map<Type, std::shared_ptr<Reflection::IBaseAttribute>> objtype_baseattribute;
		for (auto& item : m_assemblys)
		{
			auto all_attr = item.second->GetType(tp);
			for (auto& attr : all_attr)
			{
				objtype_baseattribute.emplace(attr->GetObjectType(), attr);
			}
		}
		return objtype_baseattribute;
	}

	void MEventSystem::__ObjectEventOperationHandle()
	{
		while (!m_object_event_operate.empty())
		{
			auto ctx = std::move(m_object_event_operate.front());
			m_object_event_operate.pop();
			switch (ctx.status)
			{
			case EventCtxStatus::AddEvent:
				__AddEvent(ctx);
				break;
			case EventCtxStatus::DeleteSpecificEventInObject:
				__DeleteSpecificEventInObject(ctx.self_instanceid,ctx.reg_obj_instanceid,ctx.event_id);
				break;
			default:
				break;
			}
		}
	}

	void MEventSystem::__AddEvent(const stObjectEventContext& ctx)
	{
		if (ctx.self->IsDisposed() || ctx.reg_obj->IsDisposed())return;
		if (!Exist(m_objevent_system, ctx.event_id))return;

		auto found_objevent_sys = m_objevent_system[ctx.event_id].find(ctx.reg_obj->GetObjectType().m_type);
		if (found_objevent_sys == m_objevent_system[ctx.event_id].end())
		{
			// 没找到这个对象
			return;
		}

		GetOrCreate(m_object_event, ctx.event_id)[ctx.self->InstanceId()].emplace(
			ctx.reg_obj->InstanceId(),
			std::make_pair(
				ctx.reg_obj,
				found_objevent_sys->second
			)
		);

	}


	void MEventSystem::__DeleteSpecificEventInObject(const InstanceID self_instanceid, const InstanceID reg_obj_instanceid, const uint32_t event_id, const bool cache_clear)
	{
		if (m_object_event.size() <= event_id)
		{
			throw std::exception("删除事件时类型错误，无法定位到调用信息。检查移除事件时有没有注册!");
		}
		auto found = m_object_event[event_id].find(self_instanceid);
		if (found == m_object_event[event_id].end())
		{
			return;
		}
		found->second.erase(reg_obj_instanceid);
	}

	uint32_t MEventSystem::GetOrGenEventIndex(const Type& tp)
	{
		auto found = m_eventtype_to_index.find(tp);
		if (found == m_eventtype_to_index.end())
		{
			found = m_eventtype_to_index.emplace(tp, GlobalData::GetEventIndex()).first;
		}
		return found->second;
	}

	void MEventSystem::AddObject(const std::shared_ptr<Object>& obj)
	{
		if (!m_objects.insert(std::make_pair(obj->InstanceId(), obj)).second)
		{
			throw std::exception("重复将同一个对象添加到系统中!");
		}
		TypeIndex index = obj->GetObjectType().GetTypeIndex();
		if (Exist(m_start_system,index))
		{
			m_start_enter.push(obj);
		}
		if (Exist(m_update_system,index))
		{
			m_update_enter.push(obj->InstanceId());
		}
		if (Exist(m_late_update_system,index))
		{
			m_late_update_enter.push(obj->InstanceId());
		}
	}

	void MEventSystem::RemoveObject(const std::shared_ptr<Object>& obj)
	{
		auto found = m_objects.find(obj->InstanceId());
		if (found == m_objects.end())
		{
			return;
		}
		TypeIndex index = obj->GetObjectType().GetTypeIndex();
		if (Exist(m_update_system, index))
		{
			m_update_leave.push(obj->InstanceId());
		}
		if (Exist(m_late_update_system, index))
		{
			m_late_update_leave.push(obj->InstanceId());
		}

	}

	std::shared_ptr<Object> MEventSystem::GetObject(const InstanceID id) const
	{
		auto found = m_objects.find(id);
		if (found == m_objects.end())
		{
			return nullptr;
		}
		return found->second;
	}

	void MEventSystem::Start()
	{
		std::shared_ptr<Object> obj;
		while (!m_start_enter.empty())
		{
			obj = std::move(m_start_enter.front());
			m_start_enter.pop();
			if (obj->IsDisposed())continue;
			try {
				Start(obj);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("[{}] {}", obj->GetObjectType().GetName(), e.what());
			}
			catch (...)
			{
				LOG_ERROR("[{}] 更新对象出现未知错误", obj->GetObjectType().GetName());
			}
		}
	}
	
	void MEventSystem::Update()
	{
		Start();

		while (!m_update_enter.empty())
		{
			InstanceID id = m_update_enter.front();
			m_update_enter.pop();
			auto find_obj = m_objects.find(id);
			if (find_obj == m_objects.end())
			{
				// 没找到进入的对象
				continue;
			}
			m_updates.emplace(find_obj->first, find_obj->second);
		}

		while (!m_update_leave.empty())
		{
			InstanceID id = m_update_leave.front();
			m_update_leave.pop();
			m_updates.erase(id);
		}

		for (auto& obj : m_updates)
		{
			if (obj.second->IsDisposed()) continue;
			try {
				Update(obj.second);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("[{}] {}", obj.second->GetObjectType().GetName(), e.what());
			}
			catch (...)
			{
				LOG_ERROR("[{}] 更新对象出现未知错误", obj.second->GetObjectType().GetName());
			}
		}
		Game::Time().RefreshLastTime();
	}
	
	void MEventSystem::LateUpdate()
	{
		while (!m_late_update_enter.empty())
		{
			InstanceID id = m_late_update_enter.front();
			m_late_update_enter.pop();
			auto find_obj = m_objects.find(id);
			if (find_obj == m_objects.end())
			{
				// 没找到进入的对象
				continue;
			}
			m_late_updates.emplace(find_obj->first, find_obj->second);
		}

		while (!m_late_update_leave.empty())
		{
			InstanceID id = m_late_update_leave.front();
			m_late_update_leave.pop();
			m_late_updates.erase(id);
		}

		for (auto& obj : m_late_updates)
		{
			if (obj.second->IsDisposed()) continue;
			try {
				LateUpdate(obj.second);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("[{}] {}", obj.second->GetObjectType().GetName(), e.what());
			}
			catch (...)
			{
				LOG_ERROR("[{}] 更新对象出现未知错误", obj.second->GetObjectType().GetName());
			}
		}
	}
}