#pragma once
#include <memory>
#include <unordered_set>
#include "event/GEvent.h"
#include "ObjectType.h"


class Object:
	public GEvent,
	public std::enable_shared_from_this<Object>
{
public:

	std::shared_ptr<Object> m_host;

	Object();
	~Object();

	bool IsDisposed()const {
		return m_disposed;
	}

	ObjectID GetObjectID()const {
		return m_obj_id;
	}

	std::shared_ptr<Object> Self() {
		return shared_from_this();
	}

	template<typename T>
	std::shared_ptr<T> Get() {
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}

	template<typename T>
	std::shared_ptr<T> GetHost() const {
		return std::dynamic_pointer_cast<T>(m_host);
	}
	
	const ObjectType& GetObjectType() { return m_object_type; }

public:
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
	// 唤醒通知 默认不开启
	bool CanEverAwake;
	// 唤醒通知
	virtual void Awake() {}

	// 开始通知 默认不开启
	bool CanEverStart;
	// 开始通知
	virtual void Start() {}

	// 更新通知 默认不开启
	bool CanEverUpdate;
	// 更新通知
	virtual void Update() {}

	// 更新后通知 默认不开启
	bool CanEverLateUpdate;
	// 更新后通知
	virtual void LateUpdate() {}

	// 每秒更新通知 默认不开启
	bool CanEverSecondsUpdate;
	// 每秒更新通知
	virtual void SecondsUpdate() {}

	// 销毁时通知
	virtual void Destroy() {}

private:
	friend class GameSystem;
	friend class ObjectFactory;
	friend class ObjectPool;
};