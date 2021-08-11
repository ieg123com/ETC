#pragma once
#include "type/type.h"

namespace Model
{
	/**
	 * @brief	继承的对象,将支持通过 Type 进行创建
	 */
	class ISupportTypeCreation
	{
		friend class TypeFactory;
	public:
		ISupportTypeCreation(){}
		virtual void BeginInit() {}
		virtual void EndInit() {}


	private:
		Type m_self_type;
		
	};

}