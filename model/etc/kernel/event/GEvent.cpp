#include "GEvent.h"
#include "Object.h"
#include "Game.h"
#include "EventSystem.h"

GEvent::GEvent()
{

}

GEvent::~GEvent()
{
	Clear();
}


void GEvent::Clear()
{
	while (m_event_enter.empty() == false)m_event_enter.pop();
	while (m_event_leave.empty() == false)m_event_leave.pop();
	m_all_event.clear();
	m_registered_event.clear();
}

void GEvent::EventEnter(const uint32_t id, const std::shared_ptr<Delegate>& del, const std::shared_ptr<Object>& obj)
{
	auto self = static_cast<Object*>(this);
	if (self->IsDisposed())
	{
		// 对象已经被销毁
		return;
	}
	del->set_objectid(obj->GetObjectID());
	stEnteredEvent eevent;
	eevent.target_obj = static_cast<Object*>(this)->Self();
	eevent.self_obj = obj;
	eevent.id = EventID(id, del->id(),this);
	eevent.del = del;
	m_event_enter.emplace(std::move(eevent));
}

void GEvent::EventLeave(const uint32_t id, const DelegateID& del_id, const std::shared_ptr<Object>& obj)
{
	auto self = static_cast<Object*>(this);
	if (self->IsDisposed())
	{
		// 对象已经被销毁
		return;
	}
	DelegateID del = del_id;
	del.object_id = obj->GetObjectID();
	stLeavedEvent eevent;
	eevent.target_obj = static_cast<Object*>(this)->Self();
	eevent.self_obj = obj;
	eevent.id = EventID(id, del,this);
	m_event_leave.emplace(std::move(eevent));
}

void GEvent::AddEventByDelegate(const uint32_t id, const std::shared_ptr<Delegate>& del, const std::shared_ptr<Object>& obj)
{
	auto found = m_all_event.find(id);
	if (found == m_all_event.end())
	{
		// 没有创建事件
		found = m_all_event.insert(std::make_pair(id,std::make_shared<Action>())).first;
	}
	found->second->Increase(del);

	if (obj && obj->IsDisposed() == false)
	{
		// 在函数对象中添加
		obj->m_registered_event[EventID(id, del->id(), this)] = del;
// 		if (obj->m_registered_event.insert(std::make_pair(EventID(id, del->id(), this), del)).second == false)
// 		{
// 			LOG_ERROR("添加事件失败 {}", id);
// 		}
	}
}

void GEvent::RemoveEventByDelegateID(const uint32_t id, const DelegateID& del_id, const std::shared_ptr<Object>& obj)
{
	auto found = m_all_event.find(id);
	if (found != m_all_event.end())
	{
		// 找到事件
		found->second->Remove(del_id);
	}

	if (obj && obj->IsDisposed() == false)
	{
		// 在函数对象中清除
		obj->m_registered_event.erase(EventID(id, del_id,this));
	}
}


void GEvent::HandleEvent()
{
	while (!m_event_enter.empty())
	{
		auto eevent = std::move(m_event_enter.front());
		m_event_enter.pop();
		if (eevent.del->IsDisposed())continue;
		if (eevent.target_obj->IsDisposed())continue;
		eevent.target_obj->AddEventByDelegate(eevent.id.type, eevent.del, eevent.self_obj);
	}

	while (!m_event_leave.empty())
	{
		auto eevent = std::move(m_event_leave.front());
		m_event_leave.pop();
		eevent.target_obj->RemoveEventByDelegateID(eevent.id.type, eevent.id.delegate_id, eevent.self_obj);
	}
}

