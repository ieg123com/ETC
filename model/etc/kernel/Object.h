/**
* @file		Object.h
* @author	ieg123
* @date		2021-06-23
* @brief	基类“Object”，所有对象都需要继承此类
*/
#pragma once
#include <memory>
#include <unordered_set>
#include "ObjectType.h"
#include "GameDefinition.h"
#include "interface/ISupportTypeCreation.h"

namespace Model
{
	/** @brief 基础类 */
	class Object :
		public ISupportTypeCreation,
		public std::enable_shared_from_this<Object>
	{
	public:

		/** @brief	父类对象*/
		std::shared_ptr<Object> m_host;
		/** @brief	对象id*/
		ID Id;

		Object();
		~Object();

		/**
		* @brief	获取对象是否被销毁
		* @retval	true : 已被销毁
		* @retval	false : 没有被销毁
		*/
		inline bool IsDisposed()const {
			return m_disposed;
		}
		/** @brief 实例id */
		inline InstanceID InstanceId()const {
			return m_instance_id;
		}

		/** @brief	自身对象*/
		inline std::shared_ptr<Object> Self() {
			return shared_from_this();
		}
		/**
		* @brief	获取自身对象
		* @return	返回指定类型的对象
		* @par Sample
		* @code
		*	obj->Get<Entity>();
		* @endcode
		*/
		template<typename T>
		std::shared_ptr<T> Get() {
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}
		/**
		* @brief	获取父类对象
		* @return	返回指定类型的对象
		* @par Sample
		* @code
		*	obj->GetHost<Entity>();
		* @endcode
		*/
		template<typename T>
		std::shared_ptr<T> GetHost() const {
			return std::dynamic_pointer_cast<T>(m_host);
		}

		inline const ObjectType& GetObjectType() { return m_object_type; }

		/** @brief	子对象
		 * key: id  value: child object
		 * 
		 *			        |—— Child
		 *  树形结构 Host —————— Child
		 *				    |—— Child
		 */
		std::unordered_map<ID, std::shared_ptr<Object>> Children;


		void AddChild(const std::shared_ptr<Object>& obj);

		void RemoveChild(const std::shared_ptr<Object>& obj);

		template<typename T>
		std::shared_ptr<T> GetChild(const ID id);



	public:
		/** @brief	销毁对象*/
		virtual void Dispose();

	private:
		// debug 用
		void DebugIncreaseSelf();

		// 刷新实例id
		void __RefreshInstanceId();

	private:

		// 实例id
		InstanceID	m_instance_id;
		// 对象类型
		ObjectType	m_object_type;

		bool		m_is_from_pool;

		bool		m_disposed;

	private:
		friend class GameSystem;
		friend class MEventSystem;
		friend class ObjectFactory;
		friend class ObjectPool;
	};





	inline void Object::AddChild(const std::shared_ptr<Object>& obj){
		if (Children.emplace(obj->Id, obj).second)
		{
			if (obj->m_host) obj->m_host->RemoveChild(obj);
			obj->m_host = Self();
		}
	}

	inline void Object::RemoveChild(const std::shared_ptr<Object>& obj){
		Children.erase(obj->Id);
		obj->m_host.reset();
	}

	template<typename T>
	inline std::shared_ptr<T> Object::GetChild(const ID id){
		auto found = Children.find(id);
		if (found == Children.end())
			return nullptr;
		return std::dynamic_pointer_cast<T>(found->second);
	}
}