#include "MEventSystem.h"
#include "Game.h"
#include "reflection/reflection.h"
#include "interface/ObjectSystemAttribute.h"
#include "interface/EventSystemAttribute.h"

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
				m_types.emplace(attr->GetAttrType(), attr->GetObjectType());
			}
		}

		// 默认对象事件系统
		m_awake_system.clear();
		m_load_system.clear();
		m_start_system.clear();
		m_update_system.clear();
		m_late_update_system.clear();
		m_destroy_system.clear();

		auto os_attr = m_types.equal_range(typeof(ObjectSystem));
		while (os_attr.first != os_attr.second)
		{
			auto obj = TypeFactory::CreateInstance<IEventSystem>(os_attr.first->second);
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
			++(os_attr.first);
		}



		// 自定义事件系统
		std::vector<std::pair<std::string, Type>> all_event_attr;
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
		std::vector<std::pair<std::string, Type>> all_objevent_attr;
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

	}

	void MEventSystem::RegisterObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const std::string& event_id) {
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (!self) throw std::exception("self cannot be null");
		if (event_id.empty()) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::AddEvent;
		ctx.target_obj = target_obj;
		ctx.self = self;
		ctx.event_id = event_id;
		m_object_event_operation.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const std::shared_ptr<Object>& self, const std::string& event_id)
	{
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (!self) throw std::exception("self cannot be null");
		if (event_id.empty()) throw std::exception("event_id cannot be empty");
		ctx.status = EventCtxStatus::DeleteSpecificEventInObject;
		ctx.target_obj = target_obj;
		ctx.self = self;
		ctx.event_id = event_id;
		m_object_event_operation.emplace(std::move(ctx));
	}

	void MEventSystem::RemoveObjectEvent(const std::shared_ptr<Object>& target_obj, const std::string& event_id)
	{
		static stObjectEventContext ctx;
		if (!target_obj) throw std::exception("target_obj cannot be null");
		if (event_id.empty()) throw std::exception("event_id cannot be empty");
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

		m_object_event[ctx.target_obj->GetObjectID()][ctx.event_id].insert(
			std::make_pair(
				ctx.self->GetObjectID(),
				std::make_pair(
					ctx.self,
					found_objevent_sys->second
				)
			)
		);
	}

	void MEventSystem::__DeleteAllEventInObject(const stObjectEventContext& ctx)
	{
		m_object_event.erase(ctx.target_obj->GetObjectID());
	}

	void MEventSystem::__DeleteSpecificEventInObject(const stObjectEventContext& ctx)
	{
		if (ctx.self)
		{
			// 删除到指定对象
			auto found_object_event = m_object_event.find(ctx.target_obj->GetObjectID());
			if (found_object_event == m_object_event.end())return;
			auto found_event_id = found_object_event->second.find(ctx.event_id);
			if (found_event_id == found_object_event->second.end())return;
			found_event_id->second.erase(ctx.self->GetObjectID());
		}
		else 
		{
			// 删除到指定事件id
			auto found_object_event = m_object_event.find(ctx.target_obj->GetObjectID());
			if (found_object_event == m_object_event.end())return;
			found_object_event->second.erase(ctx.event_id);
		}
	}

	void MEventSystem::AddObject(const std::shared_ptr<Object>& obj)
	{
		if (!m_objects.insert(std::make_pair(obj->GetObjectID(), obj)).second)
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
			m_update_enter.push(obj->GetObjectID());
		}
		if (Exist(m_late_update_system,index))
		{
			m_late_update_enter.push(obj->GetObjectID());
		}
	}

	void MEventSystem::RemoveObject(const std::shared_ptr<Object>& obj)
	{
		auto found = m_objects.find(obj->GetObjectID());
		if (found == m_objects.end())
		{
			return;
		}
		TypeIndex index = obj->GetObjectType().GetTypeIndex();
		if (Exist(m_update_system, index))
		{
			m_update_leave.push(obj->GetObjectID());
		}
		if (Exist(m_late_update_system, index))
		{
			m_late_update_leave.push(obj->GetObjectID());
		}

		RemoveObjectEvent(obj);

		// 重新加载热更补丁时，需要处理事件问题
	}

	std::shared_ptr<Object> MEventSystem::GetObject(const ObjectID id) const
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
			ObjectID id = m_update_enter.front();
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
			ObjectID id = m_update_leave.front();
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
			ObjectID id = m_late_update_enter.front();
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
			ObjectID id = m_late_update_leave.front();
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