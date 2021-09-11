#include "Entity.h"
#include "Component.h"
#include "ObjectFactory.h"


namespace Model
{
	std::shared_ptr<Component> GEntity::AddComponent(const std::string& name)
	{
		auto obj = ObjectFactory::TryCreateWithHost(shared_from_this(), name);
		if (auto com = obj->Get<Component>())
		{
			if (m_component.find(com->GetObjectType().GetTypeIndex()) != m_component.end())
			{
				throw std::exception("添加的组件已存在!");
			}
			m_component.insert(make_pair(com->GetObjectType().GetTypeIndex(), com));
			return com;
		}
		else {
			obj->Dispose();
			throw std::exception(("无法添加这个主键!(" + name + ")").c_str());
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
}