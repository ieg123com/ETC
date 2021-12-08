#pragma once
#include <functional>
#include "type/type.h"



namespace Model
{
	class Reflection
	{
	public:


		::Type m_type;

	};

	class IReflection
	{
	public:
		const Type& GetType()const { return m_type; }

		template<typename T>
		T* Create() {
			m_create()
		}

	private:
		::Type	m_type;

		std::function<void* ()> m_create;

		friend class ReflectionSystem;
	};


	class IReflectionSystem
	{

	};




	class ReflectionSystem
	{
	public:





	};



}