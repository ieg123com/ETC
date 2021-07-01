#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include "ObjectDebug.h"
#include "event/GEvent.h"
#include "GameDefinition.h"

class Object;


class GameSystem
{
public:

	// �������
	ObjectDebug m_ObjectDebug;

	GameSystem();
	~GameSystem();

	// ���ϵͳ����
	void AddSystem(const std::shared_ptr<Object>& object);


	// �Ƴ�ϵͳ����
	void RemoveSystem(const std::shared_ptr<Object>& object);


	// ��ȡϵͳ����
	std::shared_ptr<Object> GetSystem(const ObjectID id);

	
	void Awake(const std::shared_ptr<Object>& object);

	void Start();
	// ÿ֡����
	void Update();
	// ������
	void LateUpdate();
	// ÿ�����
	void SecondsUpdate();


	void Clear();

	size_t GetObjectNumber()const { return m_objects.size(); }

private:
	std::unordered_map<ObjectID, std::shared_ptr<Object>> m_objects;


	std::unordered_map<ObjectID, std::shared_ptr<Object>> m_updates;
	std::unordered_map<ObjectID, std::shared_ptr<Object>> m_late_updates;
	std::unordered_map<ObjectID, std::shared_ptr<Object>> m_seconds_updates;

	std::queue<std::shared_ptr<Object>>	m_start_enter;
private:
	std::queue<ObjectID>	m_update_enter;
	std::queue<ObjectID>	m_update_leave;

	std::queue<ObjectID>	m_late_update_enter;
	std::queue<ObjectID>	m_late_update_leave;

	std::queue<ObjectID>	m_seconds_update_enter;
	std::queue<ObjectID>	m_seconds_update_leave;


	friend class ObjectDebug;
};