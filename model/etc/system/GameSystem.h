#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include "ObjectDebug.h"
#include "GameDefinition.h"

namespace Model
{

	class Object;


	class GameSystem
	{
	public:

		// 对象调试
		ObjectDebug m_ObjectDebug;

		GameSystem();
		~GameSystem();

		// 添加系统对象
		void AddSystem(const std::shared_ptr<Object>& object);


		// 移除系统对象
		void RemoveSystem(const std::shared_ptr<Object>& object);


		// 获取系统对象
		std::shared_ptr<Object> GetSystem(const ObjectID id);


		//void Awake(const std::shared_ptr<Object>& object);

		void Start();
		// 每帧更新
		void Update();
		// 最后更新
		void LateUpdate();
		// 每秒更新
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

}