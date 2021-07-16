#pragma once
#include <functional>
#include "type/type.h"



namespace Model
{

	class IReflection
	{
	public:
		const Type& GetType()const { return m_type; }

		template<typename T>
		T* Create() {
			
		}

	private:
		Type	m_type;

		std::

		friend class ReflectionSystem;
	};


	class IReflectionSystem
	{

	};



}