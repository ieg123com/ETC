#pragma once
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "helper/hotfix/HotfixHelper.h"
#include "Game.h"


namespace Model
{
	void Init()
	{
		g_type_factory = new TypeFactory();
		g_singleton_factory = new ISingletonFactory();
		g_game = new GlobalGame();
	}

	stGlobalVar GetGlobalVar()
	{
		stGlobalVar global;
		global.type_factory = g_type_factory;
		global.single_factory = g_singleton_factory;
		global.game = g_game;
		return global;
	}
}