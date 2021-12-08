/**
 * @file	ISingletonManager.h
 * @author	ieg123
 * @date	2021-07-09
 * @brief	单例管理,处理热更新单例复用问题
 */
#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include "type/type_factory.h"


namespace Model
{


	/**
	 * @brief	单例类型
	 */
	enum class ESingleType : uint8_t
	{
		Module,
		Hotfix,
	};


	extern class ISingletonFactory* g_singleton_factory;

	class ISingletonFactory
	{
	public:

		template<typename T>
		static std::shared_ptr<T> Get() {
			auto found = g_singleton_factory->m_single.find(typeof(T));
			if (found == g_singleton_factory->m_single.end())
			{
				found = g_singleton_factory->m_single.insert(
					std::make_pair(
						typeof(T),
						std::make_shared<T>()
					)
				).first;
			}
			
			return std::static_pointer_cast<T>(found->second);
		}

	private:

		std::unordered_map<Type, std::shared_ptr<void>> m_single;

	};

}