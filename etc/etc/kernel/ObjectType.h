#pragma once
#include <memory>



class ObjectType
{
public:
	ObjectType() {
		m_type = &typeid(ObjectType);
	}

	const char* GetName() const {
		return (m_type->name() + 6);
	}

	const type_info* m_type;
};