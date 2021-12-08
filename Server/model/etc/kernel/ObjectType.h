#pragma once
#include <memory>
#include "type/type_factory.h"



class ObjectType
{
public:
	ObjectType() {
		m_type = typeof(class ObjectType);
	}

	const char* GetName() const {
		return (m_type.name() + 6);
	}

	inline TypeIndex GetTypeIndex() const {
		return m_type.m_info->index;
	}

	Type m_type;
};