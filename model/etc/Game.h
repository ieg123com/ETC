/**
 * @file	Game.h
 * @author	ieg123
 */
#pragma once
#include "system/GameSystem.h"
#include "system/TimeSystem.h"
#include "system/EventSystem.h"
#include "kernel/ObjectPool.h"


namespace Model
{
	class GlobalGame
	{
	public:
		GlobalGame();

		GameSystem m_System;

		TimeSystem m_Time;

		ObjectPool m_ObjPool;

		std::shared_ptr<EventSystem> m_Event;

		std::atomic<uint64_t> m_object_count;
		std::atomic<uint64_t> m_item_count;

		bool m_Stopping;
	};

	extern GlobalGame* g_game;
}

namespace Game
{

	inline GameSystem& System() { return Model::g_game->m_System; }
	inline TimeSystem& Time() { return Model::g_game->m_Time; }
	inline ObjectPool& ObjPool() { return Model::g_game->m_ObjPool; }
	inline std::shared_ptr<EventSystem>& Event() { return Model::g_game->m_Event; }
	inline std::atomic<uint64_t>& object_count() { return Model::g_game->m_object_count; }
	inline std::atomic<uint64_t>& item_count() { return Model::g_game->m_item_count; }
	inline bool& Stopping() { return Model::g_game->m_Stopping; }
};
