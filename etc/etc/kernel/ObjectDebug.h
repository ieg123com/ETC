#pragma once
#include <unordered_map>
#include <string>
#include <mutex>

// ¶ÔÏóµ÷ÊÔ
class ObjectDebug
{
public:
	~ObjectDebug();

	uint64_t ObjectCount();
	uint64_t ObjectCount(const std::string& name);

	std::string DebugObjectInfo()const;

private:
	void IncreaseObject(const std::string& name);
	void DeductObject(const std::string& name);

private:
	std::unordered_map<std::string, uint64_t>	m_objects;
	std::mutex	m_lock;

	friend class Object;
	friend class ObjectFactory;
};