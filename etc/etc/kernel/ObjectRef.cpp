#include "ObjectRef.h"




void ObjectRef::RegisterObject(const std::string& type_name, std::shared_ptr<Object>(*func)(const bool))
{
	m_ref_objects[type_name] = func;
}


std::shared_ptr<Object> ObjectRef::CreateObject(const std::string& type_name,const bool from_pool)
{
	auto found = m_ref_objects.find(type_name);
	if (found == m_ref_objects.end())
	{
		return nullptr;
	}
	return found->second(from_pool);
}
