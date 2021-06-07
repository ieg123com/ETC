#include "ObjectDebug.h"
#include "Game.h"
#include "Object.h"


ObjectDebug::~ObjectDebug()
{
	printf("析构 ObjectDebug\n");
}


void ObjectDebug::IncreaseObject(const std::string& name)
{
	std::lock_guard<std::mutex> lock(m_lock);
	auto found = m_objects.find(name);
	if (found == m_objects.end())
	{
		found = m_objects.insert(std::make_pair(name, 0)).first;
	}
	found->second++;
}

void ObjectDebug::DeductObject(const std::string& name)
{
	std::lock_guard<std::mutex> lock(m_lock);
	auto found = m_objects.find(name);
	if (found == m_objects.end())
	{
		found = m_objects.insert(std::make_pair(name, 0)).first;
	}
	found->second--;
}

uint64_t ObjectDebug::ObjectCount()
{
	uint64_t count = 0;
	for (auto& item : m_objects)
	{
		count += item.second;
	}
	return count;
}

uint64_t ObjectDebug::ObjectCount(const std::string& name)
{
	auto found = m_objects.find(name);
	if (found == m_objects.end())
	{
		return 0;
	}
	return found->second;
}

std::string ObjectDebug::DebugObjectInfo()const
{
	std::unordered_map<std::string, std::pair<uint64_t,uint64_t>>	object_info;
	for (auto& item : Game::System.m_objects)
	{
		auto found = object_info.find(item.second->GetObjectType().GetName());
		if (found == object_info.end())
		{
			found = object_info.insert(std::make_pair(item.second->GetObjectType().GetName(), std::make_pair(0,0))).first;
		}

		found->second.second++;
	}

	// =======
	uint64_t object_count = 0;
	for (auto& item : m_objects)
	{
		auto found = object_info.find(item.first);
		if (found == object_info.end())
		{
			found = object_info.insert(std::make_pair(item.first, std::make_pair(0, 0))).first;
		}

		found->second.first += item.second;
		object_count += item.second;
	}
	// End


	std::string info_str;
	info_str = "全部对象数: " + std::to_string(object_count) + " | " + std::to_string(Game::System.m_objects.size());
	for (auto& item : object_info)
	{
		info_str += "\n[" + item.first + "] 对象数: " + std::to_string(item.second.first) + " | " + std::to_string(item.second.second);
	}
	return std::move(info_str);
}