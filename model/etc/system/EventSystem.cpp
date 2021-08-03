#include "EventSystem.h"
#include "Game.h"

namespace Model
{
	EventSystem::EventSystem()
	{
	}





	void EventSystem::AddObject(const std::shared_ptr<Object>& obj)
	{
		if (m_objects.insert(std::make_pair(obj->GetObjectID(), obj)).second)
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

	void EventSystem::RemoveObject(const std::shared_ptr<Object>& obj)
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
		// 重新加载热更补丁时，需要处理事件问题
	}

	std::shared_ptr<Object> EventSystem::GetObject(const ObjectID id) const
	{
		auto found = m_objects.find(id);
		if (found == m_objects.end())
		{
			return nullptr;
		}
		return found->second;
	}

	void EventSystem::Start()
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
	
	void EventSystem::Update()
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
	
	void EventSystem::LateUpdate()
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