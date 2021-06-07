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


	// ���㽫�����͵�����������
	// �������䴫�Ͷ������м̳�Object�Ķ�����봦�����нӿ�
	// ��Json�н�������
	virtual bool ParseFromJson(const Json& json) { return false; };
	// ���л�����Json
	virtual bool SerializeToJson(const Json& json) const { return false; };

private:
	// debug ��
	void DebugIncreaseSelf();

	// ˢ�¶���id
	void RefreshObjectID();

private:
	

	ObjectID	m_obj_id;
	// ��������
	ObjectType	m_object_type;

	bool		m_is_from_pool;

	bool		m_disposed;

protected:
	// ����֪ͨ Ĭ�ϲ�����
	bool CanEverAwake;
	// ����֪ͨ
	virtual void Awake() {}

	// ��ʼ֪ͨ Ĭ�ϲ�����
	bool CanEverStart;
	// ��ʼ֪ͨ
	virtual void Start() {}

	// ����֪ͨ Ĭ�ϲ�����
	bool CanEverUpdate;
	// ����֪ͨ
	virtual void Update() {}

	// ���º�֪ͨ Ĭ�ϲ�����
	bool CanEverLateUpdate;
	// ���º�֪ͨ
	virtual void LateUpdate() {}

	// ÿ�����֪ͨ Ĭ�ϲ�����
	bool CanEverSecondsUpdate;
	// ÿ�����֪ͨ
	virtual void SecondsUpdate() {}

	// ����ʱ֪ͨ
	virtual void Destroy() {}

private:
	friend class GameSystem;
	friend class ObjectFactory;
	friend class ObjectPool;
};