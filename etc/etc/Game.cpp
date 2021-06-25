#include "Game.h"
#include "system/EventSystem.h"
#include "kernel/ObjectPool.h"
#include "ObjectFactory.h"
#include <atomic>



namespace Game
{
	GameSystem System;

	TimeSystem Time;

	ObjectPool ObjPool;

	std::shared_ptr<EventSystem> Event = ObjectFactory::Create<EventSystem>();

	std::atomic<uint64_t> object_count = 0;
	std::atomic<uint64_t> item_count = 0;

	bool Stopping = false;
}
