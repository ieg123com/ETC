/**
 * @file	Game.h
 * @author	ieg123
 */
#pragma once
#include "system/GameSystem.h"
#include "system/TimeSystem.h"
#include "system/EventSystem.h"
#include "kernel/ObjectPool.h"



namespace Game
{

	extern GameSystem System;

	extern TimeSystem Time;

	extern ObjectPool ObjPool;

	extern std::shared_ptr<EventSystem> Event;

	extern std::atomic<uint64_t> object_count;
	extern std::atomic<uint64_t> item_count;

	extern bool Stopping;
};