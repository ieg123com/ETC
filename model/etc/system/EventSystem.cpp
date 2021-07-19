#include "EventSystem.h"

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
		auto tp = obj->GetObjectType().m_type;
		if (m_start_system.find(tp) != m_start_system.end())
		{
			m_start_enter.push(obj);
		}
		if (m_update_system.find(tp) != m_update_system.end())
		{
			m_update_enter.push(obj->GetObjectID());
		}
		if (m_late_update_system.find(tp) != m_late_update_system.end())
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
}