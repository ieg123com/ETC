#pragma once
#include "Game.h"

class ObjectFactory
{
public:

	template<typename T>
	static std::shared_ptr<T> Create(const bool from_pool = true) {
		// �������̳� Object
		static_assert(std::is_base_of<Object, T>::value,
			"The create object must inherit Object!");
		auto obj = InternalCreate<T>(from_pool);
		Game::System.Awake(obj);
		return obj;
	}

	static std::shared_ptr<Object> Create(const std::string& type_name, const bool from_pool = true);
	static std::shared_ptr<Object> TryCreate(const std::string& type_name, const bool from_pool = true);

	template<typename T>
	static std::shared_ptr<T> CreateWithHost(const std::shared_ptr<Object>& host,const bool from_pool = true) {
		// �������̳� Object
		static_assert(std::is_base_of<Object, T>::value,
			"The create object must inherit Object!");
		auto obj = InternalCreate<T>(from_pool);
		obj->m_host = host;
		Game::System.Awake(obj);
		return obj;
	}

	static std::shared_ptr<Object> CreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool = true);
	static std::shared_ptr<Object> TryCreateWithHost(const std::shared_ptr<Object>& host, const std::string& type_name, const bool from_pool = true);



	template<typename T>
	static std::shared_ptr<T> InternalCreate(const bool from_pool) {
		// �������̳� Object
		static_assert(std::is_base_of<Object, T>::value,
			"The create object must inherit Object!");
		std::shared_ptr<T> obj;
		// �Ȳ���������أ���ֹ������ݳ�����
//  		if (from_pool)
//  		{
//  			obj = Game::ObjPool.Fetch<T>();
//  		}
// 		else
		{
			obj = std::make_shared<T>();
			obj->m_object_type.m_type = &typeid(T);
			obj->DebugIncreaseSelf();
		}
		Game::System.AddSystem(obj);
		return obj;
	}

	static std::shared_ptr<Object> InternalCreate(const std::string& type_name, const bool from_pool);

};