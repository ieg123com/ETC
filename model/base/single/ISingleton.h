/**
 * @file	ISingleton.h
 * @author	ieg123
 * @date	2021-07-09
 * @brief	单例模式
 */

#pragma once
#include <memory>
#include <mutex>
#include "ISingletonHandle.h"

namespace Model
{
	/**
	 * @brief	所有域中都为单例模式
	 */
	template<typename T>
	class ISingleton
	{
	public:

		static T& Instance() {
			static std::mutex lock;
			if (!m_Instance)
			{
				lock.lock();
				if (!m_Instance)
				{
					m_Instance = ISingletonFactory::Get<T>();
				}
				lock.unlock();
			}
			return *m_Instance;
		}

		static std::shared_ptr<T> GetSharedPtr() {
			return m_Instance;
		}

	protected:
		ISingleton() {}
		~ISingleton() {}

	private:
		static std::shared_ptr<T>	m_Instance;
	};

	template <typename T>
	std::shared_ptr<T> ISingleton<T>::m_Instance;


	/**
	 * @brief	只在当前域中为单例
	 */
	template<typename T>
	class IDomainSingleton
	{
	public:

		static T& Instance() {
			static std::mutex lock;
			if (!m_Instance)
			{
				lock.lock();
				if (!m_Instance)
				{
					m_Instance = std::make_shared<T>();
				}
				lock.unlock();
			}
			return *m_Instance;
		}

		static std::shared_ptr<T> GetSharedPtr() {
			if (!m_Instance)Instance();
			return m_Instance;
		}

	protected:
		IDomainSingleton() {}
		~IDomainSingleton() {}

	private:
		static std::shared_ptr<T>	m_Instance;
	};

	template <typename T>
	std::shared_ptr<T> IDomainSingleton<T>::m_Instance;
}