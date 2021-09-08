#pragma once
#include "Game.h"

namespace Model
{

	class ObjectFactory
	{
	public:

		template<typename T>
		static std::shared_ptr<T> Create(const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T,typename A>
		static std::shared_ptr<T> Create(A a,const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			Game::Event().Awake<A>(obj,a);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T, typename A,typename B>
		static std::shared_ptr<T> Create(A a,B b, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			Game::Event().Awake<A,B>(obj, a,b);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T, typename A, typename B,typename C>
		static std::shared_ptr<T> Create(A a, B b,C c, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			Game::Event().Awake<A, B,C>(obj, a, b,c);
			Game::Event().Load(obj);
			return obj;
		}

		static std::shared_ptr<Object> Create(const std::string& type_name, const bool from_pool = false);
		static std::shared_ptr<Object> TryCreate(const std::string& type_name, const bool from_pool = false);

		template<typename T>
		static std::shared_ptr<T> CreateWithHost(const std::shared_ptr<Object>& host, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			obj->m_host = host;
			Game::Event().Awake(obj);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T,typename A>
		static std::shared_ptr<T> CreateWithHost(const std::shared_ptr<Object>& host,A a, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			obj->m_host = host;
			Game::Event().Awake<A>(obj,a);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T, typename A,typename B>
		static std::shared_ptr<T> CreateWithHost(const std::shared_ptr<Object>& host, A a, B b, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			obj->m_host = host;
			Game::Event().Awake<A,B>(obj, a,b);
			Game::Event().Load(obj);
			return obj;
		}

		template<typename T, typename A, typename B,typename C>
		static std::shared_ptr<T> CreateWithHost(const std::shared_ptr<Object>& host, A a, B b,C c, const bool from_pool = false) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			auto obj = InternalCreate<T>(from_pool);
			obj->m_host = host;
			Game::Event().Awake<A, B,C>(obj, a, b,c);
			Game::Event().Load(obj);
			return obj;
		}

		static std::shared_ptr<Object> CreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool = false);
		static std::shared_ptr<Object> TryCreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool = false);



		template<typename T>
		static std::shared_ptr<T> InternalCreate(const bool from_pool) {
			// 对象必须继承 Object
			static_assert(std::is_base_of<Object, T>::value,
				"The create object must inherit Object!");
			std::shared_ptr<T> obj;
			// 先不开启对象池，防止玩家数据出问题
	//  		if (from_pool)
	//  		{
	//  			obj = Game::ObjPool.Fetch<T>();
	//  		}
	// 		else
			{
				obj = std::make_shared<T>();
				obj->BeginInit();
				obj->m_object_type.m_type = typeof(T);
				obj->DebugIncreaseSelf();
				obj->EndInit();
			}
			Game::Event().AddObject(obj);
			return obj;
		}

		static std::shared_ptr<Object> InternalCreate(const std::string& type_name, const bool from_pool);

	};
}