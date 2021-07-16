#pragma once
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "helper/hotfix/HotfixHelper.h"
#include "task/domain_task.h"
#include "GlobalData.h"
#include "Game.h"


namespace Model
{
	void Init()
	{
		g_type_factory = new TypeFactory();
		g_singleton_factory = new ISingletonFactory();
		g_global_data = new GlobalData();
		g_game = new GlobalGame();
		g_game->Init();

		DomainTask::Instance().RunAll();
	}

	stGlobalVar GetGlobalVar()
	{
		stGlobalVar global;
		global.type_factory = g_type_factory;
		global.single_factory = g_singleton_factory;
		global.global_data = g_global_data;
		global.game = g_game;
		return global;
	}

	void SetGlobalVar(const stGlobalVar& global)
	{
		g_type_factory = global.type_factory;
		g_singleton_factory = global.single_factory;
		g_global_data = global.global_data;
		g_game = global.game;
	}
}