#pragma once
#include <functional>
#include "type/type.h"
#include "attribute/attribute.h"


namespace Model
{
	namespace Reflection
	{

		class IBaseAttribute:
			public Attribute
		{
		public:
			Type m_attr_type;
			Type m_obj_type;

			const Type& GetAttrType() const { return m_attr_type; }
			const Type& GetObjectType() const { return m_obj_type; }
		};

		/**
		 * @brief	反射基础属性,用于继承
		 */
		template<typename T>
		class BaseAttribute:
			public IBaseAttribute
		{
		public:
			BaseAttribute() {
				m_attr_type = typeof(T);
			}
		};

	}

}