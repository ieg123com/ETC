﻿/**
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

		GameSystem m_System;

		TimeSystem m_Time;

		ObjectPool m_ObjPool;

		EventSystem m_Event;

		std::atomic<uint64_t> m_object_count;
		std::atomic<uint64_t> m_item_count;

		bool m_Stopping;

		void Init();
	};

	extern GlobalGame* g_game;

	class Game
	{
	public:
		static inline GameSystem& System() { return Model::g_game->m_System; }
		static inline TimeSystem& Time() { return Model::g_game->m_Time; }
		static inline ObjectPool& ObjPool() { return Model::g_game->m_ObjPool; }
		static inline EventSystem& Event() { return Model::g_game->m_Event; }
		static inline std::atomic<uint64_t>& object_count() { return Model::g_game->m_object_count; }
		static inline std::atomic<uint64_t>& item_count() { return Model::g_game->m_item_count; }
		static inline bool& Stopping() { return Model::g_game->m_Stopping; }
	};
}

