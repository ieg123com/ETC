#pragma once
#include "Object.h"
#include <unordered_map>

class Component;

class Entity :
	public Object
{
public:

	template<typename T>
	std::shared_ptr<T> AddComponent() {

		if (m_component.find(&typeid(T)) != m_component.end())
		{
			throw std::exception("添加的组件已存在!");
		}
		auto obj = ObjectFactory::CreateWithHost<T>(shared_from_this());

		m_component.insert(std::make_pair(&typeid(T), obj));

		return obj;
	}

	std::shared_ptr<Component> AddComponent(const std::string& name);

	template<typename T>
	std::shared_ptr<T> GetComponent() {
		auto find_obj = m_component.find(&typeid(T));
		if (find_obj == m_component.end())
		{
			return nullptr;
		}
		return std::dynamic_pointer_cast<T>(find_obj->second);
	}

	template<typename T>
	void RemoveComponent() {
		auto find_obj = m_component.find(&typeid(T));
		if (find_obj != m_component.end())
		{
			auto obj = find_obj->second;
			m_component.erase(find_obj);

			obj->Dispose();
		}
	}


	virtual void Dispose() override;

private:
	std::unordered_map<const type_info*, std::shared_ptr<Component>>	m_component;



};

