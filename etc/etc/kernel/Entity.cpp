﻿#include "Entity.h"
#include "Component.h"
#include "ObjectFactory.h"



std::shared_ptr<Component> Entity::AddComponent(const std::string& name)
{
	auto obj = ObjectFactory::TryCreateWithHost(shared_from_this(), name);
	if (auto com = obj->Get<Component>())
	{
		if (m_component.find(com->GetObjectType().m_type) != m_component.end())
		{
			throw std::exception("添加的组件已存在!");
		}
		m_component.insert(std::make_pair(com->GetObjectType().m_type, com));
		return com;
	}
	else {
		obj->Dispose();
		throw std::exception(("无法添加这个主键!("+ name +")").c_str());
	}
}

void Entity::Dispose() {
	if (Object::IsDisposed()) {
		return;
	}
	else {

		for (auto& com : m_component)
		{
			com.second->Dispose();
		}
		m_component.clear();

		Object::Dispose();
	}
}