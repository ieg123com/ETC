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

		// 默认对象事件系统
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
				if (obj)
					LOG_INFO("Awake sytem {}:{}", attr.full_name(), attr.m_info->index);
				else
					LOG_ERROR("Awake sytem {}:{}", attr.full_name(), attr.m_info->index);

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


		// 自定义事件系统
		std::vector<std::pair<int32_t, Type>> all_event_attr;
		for (auto& item : m_assemblys)
		{
			auto all_attr = item.second->GetType<Event>();
			for (auto& attr : all_attr)
			{
				if (auto eattr = std::dynamic_pointer_cast<Event>(attr))
				{
					all_event_attr.emplace_back(eattr->EventId, eattr->GetObjectType());
				}
			}
		}

		m_event_system.clear();
		for (auto& event_attr : all_event_attr)
		{
			if (auto event_obj = TypeFactory::CreateInstance<IEventSystem>(event_attr.second))
			{
				m_event_system.emplace(event_attr.first, event_obj);
			}
		}


		// 自定义对象事件系统
		std::vector<std::pair<int32_t, Type>> all_objevent_attr;
		for (auto& item : m_assemblys)
		{
			auto all_attr = item.second->GetType<ObjEvent>();
			for (auto& attr : all_attr)
			{
				if (auto eattr = std::dynamic_pointer_cast<ObjEvent>(attr))
				{
					all_objevent_attr.emplace_back(eattr->EventId, eattr->GetObjectType());
				}
			}
		}

		m_objevent_system.clear();
		for (auto& event_attr : all_objevent_attr)
		{
			if (auto event_obj = TypeFactory::CreateInstance<IObjEventSystem>(event_attr.second))
			{
				m_objevent_system.emplace(std::make_pair(event_attr.first,event_obj->GetType()), event_obj);
			}
		}


		{
			// 自定义对象事件清除
			m_object_event.clear();
			while(!m_object_event_operation.empty())m_object_event_operation.pop();
			
			for (auto& item : m_objects)
			{
				Load(item.second);
			}
		}

	}

	void MEventSystem::RegisterObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const int32_t event_id) {
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (!self) throw std::exception("self cannot be null");
		if (event_id == 0) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::AddEvent;
		ctx.target_obj = target_obj;
		ctx.self = self;
		ctx.event_id = event_id;
		m_object_event_operation.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const int32_t event_id)
	{
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (!self) throw std::exception("self cannot be null");
		if (event_id == 0) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::DeleteSpecificEventInObject;
		ctx.target_obj = target_obj;
		ctx.self = self;
		ctx.event_id = event_id;
		m_object_event_operation.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const int32_t event_id)
	{
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (event_id == 0) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::DeleteSpecificEventInObject;
		ctx.target_obj = target_obj;
		ctx.event_id = event_id;
		m_object_event_operation.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& target_obj)
	{
		stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		ctx.status = EventCtxStatus::DeleteAllEventInObject;
		ctx.target_obj = target_obj;
		m_object_event_operation.emplace(std::move(ctx));
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
		while (!m_object_event_operation.empty())
		{
			auto ctx = std::move(m_object_event_operation.front());
			m_object_event_operation.pop();
			switch (ctx.status)
			{
			case EventCtxStatus::AddEvent:
				__AddEvent(ctx);
				break;
			case EventCtxStatus::DeleteAllEventInObject:
				__DeleteAllEventInObject(ctx);
				break;
			case EventCtxStatus::DeleteSpecificEventInObject:
				__DeleteSpecificEventInObject(ctx);
				break;
			default:
				break;
			}
		}
	}

	void MEventSystem::__AddEvent(const stObjectEventContext& ctx)
	{
		auto found_objevent_sys = m_objevent_system.find(std::make_pair(ctx.event_id,ctx.self->GetObjectType().m_type));
		if (found_objevent_sys == m_objevent_system.end())
		{
			return;
		}

		m_object_event[ctx.target_obj->InstanceId()][ctx.event_id].insert(
			std::make_pair(
				ctx.self->InstanceId(),
				std::make_pair(
					ctx.self,
					found_objevent_sys->second
				)
			)
		);
	}

	void MEventSystem::__DeleteAllEventInObject(const stObjectEventContext& ctx)
	{
		m_object_event.erase(ctx.target_obj->InstanceId());
	}

	void MEventSystem::__DeleteSpecificEventInObject(const stObjectEventContext& ctx)
	{
		if (ctx.self)
		{
			// 删除到指定对象
			auto found_object_event = m_object_event.find(ctx.target_obj->InstanceId());
			if (found_object_event == m_object_event.end())return;
			auto found_event_id = found_object_event->second.find(ctx.event_id);
			if (found_event_id == found_object_event->second.end())return;
			found_event_id->second.erase(ctx.self->InstanceId());
		}
		else 
		{
			// 删除到指定事件id
			auto found_object_event = m_object_event.find(ctx.target_obj->InstanceId());
			if (found_object_event == m_object_event.end())return;
			found_object_event->second.erase(ctx.event_id);
		}
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

		RemoveObjectEvent(obj);

		// 重新加载热更补丁时，需要处理事件问题
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