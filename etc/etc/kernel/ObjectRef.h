#pragma once
#include <memory>
#include <unordered_map>
#include <string>

class Object;

// �������
class ObjectRef
{
public:

	static ObjectRef& Instance() {
		static ObjectRef self;
		return self;
	}

	// ע�����
	void RegisterObject(const std::string& type_name, std::shared_ptr<Object>(*func)(const bool));

	// ��������
	std::shared_ptr<Object> CreateObject(const std::string& type_name, const bool from_pool = true);

private:

	// ��������¼
	std::unordered_map<std::string, std::shared_ptr<Object>(*)(const bool)>	m_ref_objects;

	
};

