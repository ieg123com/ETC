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

namespace Model
{
	/** @brief 基础类 */
	class Object :
		public std::enable_shared_from_this<Object>
	{
	public:

		/** @brief	父类对象*/
		std::shared_ptr<Object> m_host;

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

		inline ObjectID GetObjectID()const {
			return m_obj_id;
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

	public:
		/** @brief	销毁对象*/
		virtual void Dispose();


		// 方便将对象发送到其他服务器
		// 服务器间传送对象，所有继承Object的对象必须处理下列接口
		// 从Json中解析对象
		virtual bool ParseFromJson(const Json& json) { return false; };
		// 序列化对象到Json
		virtual bool SerializeToJson(const Json& json) const { return false; };

	private:
		// debug 用
		void DebugIncreaseSelf();

		// 刷新对象id
		void RefreshObjectID();

	private:


		ObjectID	m_obj_id;
		// 对象类型
		ObjectType	m_object_type;

		bool		m_is_from_pool;

		bool		m_disposed;

	protected:
		/** @brief	唤醒通知 默认不开启*/
		bool CanEverAwake;
		/** @brief	唤醒通知*/
		virtual void Awake() {}

		/** @brief	开始通知 默认不开启*/
		bool CanEverStart;
		/** @brief	开始通知*/
		virtual void Start() {}

		/** @brief	更新通知 默认不开启*/
		bool CanEverUpdate;
		/** @brief	更新通知*/
		virtual void Update() {}

		/** @brief	更新后通知 默认不开启*/
		bool CanEverLateUpdate;
		/** @brief	更新后通知*/
		virtual void LateUpdate() {}

		/** @brief	每秒更新通知 默认不开启*/
		bool CanEverSecondsUpdate;
		/** @brief	每秒更新通知*/
		virtual void SecondsUpdate() {}

		/** @brief	销毁时通知*/
		virtual void Destroy() {}

	private:
		friend class GameSystem;
		friend class ObjectFactory;
		friend class ObjectPool;
	};
}