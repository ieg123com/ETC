#pragma once
#include <memory>
#include "type/type.h"



class ObjectType
{
public:
	ObjectType() {
		m_type = typeof(class ObjectType);
	}

	const char* GetName() const {
		return (m_type.name() + 6);
	}

	Type m_type;
};