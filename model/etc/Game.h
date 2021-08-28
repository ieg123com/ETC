/**
 * @file	Game.h
 * @author	ieg123
 */
#pragma once
#include "system/GameSystem.h"
#include "system/TimeSystem.h"
#include "system/MEventSystem.h"
#include "kernel/ObjectPool.h"
#include "entity/World.h"
#include "module/component/Options.h"


namespace Model
{
	class GlobalGame
	{
	public:
		static GlobalGame* Instance;
		
		std::shared_ptr<World> m_World;

		GameSystem m_System;

		TimeSystem m_Time;

		ObjectPool m_ObjPool;

		MEventSystem m_Event;

		Options	m_Options;

		std::atomic<uint64_t> m_object_count;
		std::atomic<uint64_t> m_item_count;


		bool m_Stopping;

		void Init();
	};

	class Game
	{
	public:
		static inline std::shared_ptr<World> World() { return Model::GlobalGame::Instance->m_World; }
		static inline GameSystem& System() { return Model::GlobalGame::Instance->m_System; }
		static inline TimeSystem& Time() { return Model::GlobalGame::Instance->m_Time; }
		static inline ObjectPool& ObjPool() { return Model::GlobalGame::Instance->m_ObjPool; }
		static inline MEventSystem& Event() { return Model::GlobalGame::Instance->m_Event; }
		static inline Options& Options() { return Model::GlobalGame::Instance->m_Options; }
		static inline std::atomic<uint64_t>& object_count() { return Model::GlobalGame::Instance->m_object_count; }
		static inline std::atomic<uint64_t>& item_count() { return Model::GlobalGame::Instance->m_item_count; }
		static inline bool& Stopping() { return Model::GlobalGame::Instance->m_Stopping; }
	};
}

