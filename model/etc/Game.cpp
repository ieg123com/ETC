#include "Game.h"
#include "system/EventSystem.h"
#include "kernel/ObjectPool.h"
#include "ObjectFactory.h"
#include <atomic>

namespace Model
{
	GlobalGame::GlobalGame()
	{
		m_Event = ObjectFactory::Create<EventSystem>();
		m_object_count = 0;
		m_item_count = 0;
		m_Stopping = false;
	}

	GlobalGame* g_game = nullptr;
}


