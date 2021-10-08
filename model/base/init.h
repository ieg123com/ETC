#pragma once
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "helper/hotfix/HotfixHelper.h"
#include "task/domain_task.h"
#include "reflection/reflection.h"
#include "kernel/ObjectFactory.h"
#include "kernel/IdGenerator.h"
#include "async/async.h"
#include "thread/MainThreadContext.h"
#include "GlobalData.h"
#include "Game.h"

using namespace Model::Reflection;

namespace Model
{
	void ParseArguments(int argc, char* argv[])
	{
		for (int i = 0; i < argc; ++i)
		{
			std::string arg = argv[i];
			size_t pos = arg.find('=');
			if (pos == std::string::npos)continue;
			std::string key = arg.substr(2, pos - 2);
			std::string value = arg.substr(pos + 1, arg.size() - pos - 1);
			LOG_WARN("key {} value {}", key, value);
			if (key == "ProcessId")
			{
				Game::Options().ProcessId = std::to<int32_t>(value);
			}
			if (key == "ProcessType")
			{
				Game::Options().ProcessType = ToProcessType(value);
			}
		}
	}

	void Init(int argc, char* argv[])
	{
		g_type_factory = new TypeFactory();
		g_singleton_factory = new ISingletonFactory();
		GlobalData::Instance = new GlobalData();
		GlobalGame::Instance = new GlobalGame();
		IdGenerator::Instance = new IdGenerator();
		async::Scheduler::Instance = new async::Scheduler();
		MainThreadContext::Instance = new MainThreadContext();
		GlobalGame::Instance->Init();

		ParseArguments(argc, argv);
		LOG_INFO("========== ParseArguments ==========");


		DomainTask::Instance().RunAll();

		Game::Event().Add(DLLType::Model, Assembly::GetSharedPtr());

		GlobalGame::Instance->m_World = ObjectFactory::Create<World>();

	}

	stGlobalVar GetGlobalVar()
	{
		stGlobalVar global;
		global.type_factory = g_type_factory;
		global.single_factory = g_singleton_factory;
		global.global_data = GlobalData::Instance;
		global.game = GlobalGame::Instance;
		global.id_generator = IdGenerator::Instance;
		global.async_scheduler = async::Scheduler::Instance;
		global.main_thread_context = MainThreadContext::Instance;
		return global;
	}

	void SetGlobalVar(const stGlobalVar& global)
	{
		g_type_factory = global.type_factory;
		g_singleton_factory = global.single_factory;
		GlobalData::Instance = global.global_data;
		GlobalGame::Instance = global.game;
		IdGenerator::Instance = global.id_generator;
		async::Scheduler::Instance = global.async_scheduler;
		MainThreadContext::Instance = global.main_thread_context;
	}
}