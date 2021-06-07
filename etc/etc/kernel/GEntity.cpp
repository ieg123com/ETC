#include "GEntity.h"
#include "Component.h"
#include "ObjectFactory.h"



std::shared_ptr<Component> GEntity::AddComponent(const std::string& name)
{
	auto obj = ObjectFactory::TryCreateWithHost(shared_from_this(), name);
	if (auto com = obj->Get<Component>())
	{
		if (m_component.find(com->GetObjectType().m_type) != m_component.end())
		{
			throw std::exception("��ӵ�����Ѵ���!");
		}
		m_component.insert(std::make_pair(com->GetObjectType().m_type, com));
		return com;
	}
	else {
		obj->Dispose();
		throw std::exception(("�޷�����������!("+ name +")").c_str());
	}
}

void GEntity::Dispose() {
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