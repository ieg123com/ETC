/**
 * @file	ISingleton.h
 * @author	ieg123
 * @date	2021-07-09
 * @brief	µ¥ÀýÄ£Ê½
 */

#pragma once
#include <memory>
#include "ISingletonHandle.h"

namespace Model
{
	template<typename T>
	class ISingleton
	{
	public:

		static T& Instance() {
			if (!m_Instance)
			{
				m_Instance = ISingletonFactory::Get<T>();
			}
			return *m_Instance;
		}

	protected:
		ISingleton() {}
		~ISingleton() {}

	private:
		static std::shared_ptr<T>	m_Instance;
	};

	template <typename T>
	std::shared_ptr<T> ISingleton<T>::m_Instance;

}

