#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace Model
{
	class Object;
};

// 反射初版
class ObjectRef
{
public:

	static ObjectRef& Instance() {
		static ObjectRef self;
		return self;
	}

	// 注册对象
	void RegisterObject(const std::string& type_name, std::shared_ptr<Model::Object>(*func)(const bool));

	// 创建对象
	std::shared_ptr<Model::Object> CreateObject(const std::string& type_name, const bool from_pool = true);

private:

	// 反射对象记录
	std::unordered_map<std::string, std::shared_ptr<Model::Object>(*)(const bool)>	m_ref_objects;

	
};

