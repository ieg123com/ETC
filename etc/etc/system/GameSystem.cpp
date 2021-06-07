#include "GameSystem.h"
#include "Object.h"
#include "EventSystem.h"
#include "Game.h"

#include "log/log.h"

GameSystem::GameSystem()
{
	
}

GameSystem::~GameSystem()
{
	Clear();
}


void GameSystem::AddSystem(const std::shared_ptr<Object>& object)
{
	m_objects.insert(std::make_pair(object->m_obj_id, object));

	if (object->CanEverStart)
	{
		m_start_enter.push(object);
	}
	if (object->CanEverUpdate)
	{
		m_update_enter.push(object->m_obj_id);
	}
	if (object->CanEverLateUpdate)
	{
		m_late_update_enter.push(object->m_obj_id);
	}
	if (object->CanEverSecondsUpdate)
	{
		m_seconds_update_enter.push(object->m_obj_id);
	}
}

void GameSystem::RemoveSystem(const std::shared_ptr<Object>& object)
{
	m_objects.erase(object->m_obj_id);
	
	if (object->CanEverUpdate)
	{
		m_update_leave.push(object->m_obj_id);
	}
	if (object->CanEverLateUpdate)
	{
		m_late_update_leave.push(object->m_obj_id);
	}
	if (object->CanEverSecondsUpdate)
	{
		m_seconds_update_leave.push(object->m_obj_id);
	}
}

std::shared_ptr<Object> GameSystem::GetSystem(const ObjectID id)
{
	auto find_obj = m_objects.find(id);
	if (find_obj == m_objects.end())
	{
		return nullptr;
	}
	return find_obj->second;
}


void GameSystem::Awake(const std::shared_ptr<Object>& object)
{
	if (object->CanEverAwake)
	{
		object->Awake();
	}
}

void GameSystem::Start()
{
	std::shared_ptr<Object> obj;
	while (!m_start_enter.empty())
	{
		obj = std::move(m_start_enter.front());
		m_start_enter.pop();
		if (obj->IsDisposed())continue;
		try {
			obj->Start();
		}
		catch (std::exception & e)
		{
			LOG_ERROR("[{}] {}", obj->GetObjectType().GetName(), e.what());
		}
		catch (...)
		{
			LOG_ERROR("[{}] 更新对象出现未知错误", obj->GetObjectType().GetName());
		}
	}
}

void GameSystem::Update() 
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
		if(obj.second->IsDisposed()) continue;
		try {
			obj.second->Update();
		}
		catch (std::exception & e)
		{
			LOG_ERROR("[{}] {}", obj.second->GetObjectType().GetName(), e.what());
		}
		catch (...)
		{
			LOG_ERROR("[{}] 更新对象出现未知错误", obj.second->GetObjectType().GetName());
		}
	}
	Game::Time.RefreshLastTime();
}

void GameSystem::LateUpdate()
{
	Start();

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
		m_late_updates.emplace(find_obj->first,find_obj->second);
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
			obj.second->LateUpdate();
		}
		catch (std::exception & e)
		{
			LOG_ERROR("[{}] {}", obj.second->GetObjectType().GetName(), e.what());
		}
		catch (...)
		{
			LOG_ERROR("[{}] 更新对象出现未知错误", obj.second->GetObjectType().GetName());
		}
	}
}

void GameSystem::SecondsUpdate()
{
	Start();

	while (!m_seconds_update_enter.empty())
	{
		ObjectID id = m_seconds_update_enter.front();
		m_seconds_update_enter.pop();
		auto find_obj = m_objects.find(id);
		if (find_obj == m_objects.end())
		{
			// 没找到进入的对象
			continue;
		}
		m_seconds_updates.emplace(find_obj->first,find_obj->second);
	}

	while (!m_seconds_update_leave.empty())
	{
		ObjectID id = m_seconds_update_leave.front();
		m_seconds_update_leave.pop();
		m_seconds_updates.erase(id);
	}

	for (auto& obj : m_seconds_updates)
	{
		if (obj.second->IsDisposed()) continue;
		try {
			obj.second->SecondsUpdate();
		}
		catch (std::exception & e)
		{
			LOG_ERROR("[{}] {}", obj.second->GetObjectType().GetName(), e.what());
		}
		catch (...)
		{
			LOG_ERROR("[{}] 更新对象出现未知错误", obj.second->GetObjectType().GetName());
		}
	}
}


void GameSystem::Clear()
{
	for (auto& obj : m_updates)
	{
		obj.second->Dispose();
	}
	Update();
}

