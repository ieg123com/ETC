#pragma once
#include "single/ISingletonHandle.h"
#include "type/type.h"
#include "helper/hotfix/HotfixHelper.h"
#include "task/domain_task.h"
#include "reflection/reflection.h"
#include "kernel/ObjectFactory.h"
#include "kernel/IdGenerator.h"
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
			if (key == "AppId")
			{
				Game::Options().AppId = std::to<int32_t>(value);
			}
			if (key == "AppType")
			{
				Game::Options().AppType = ToAppType(value);
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
		GlobalGame::Instance->Init();

		ParseArguments(argc, argv);
		LOG_INFO("========== ParseArguments ==========");


		DomainTask::Instance().RunAll();

		Game::Event().Add(DLLType::Model, Assembly::GetSharedPtr());

		InstanceIdStruct instance_id_struct;
		instance_id_struct.process = Game::Options().AppId;
		GlobalGame::Instance->m_World = ObjectFactory::CreateWithInstanceId<World>(instance_id_struct.ToLong());

	}

	stGlobalVar GetGlobalVar()
	{
		stGlobalVar global;
		global.type_factory = g_type_factory;
		global.single_factory = g_singleton_factory;
		global.global_data = GlobalData::Instance;
		global.game = GlobalGame::Instance;
		global.id_generator = IdGenerator::Instance;
		return global;
	}

	void SetGlobalVar(const stGlobalVar& global)
	{
		g_type_factory = global.type_factory;
		g_singleton_factory = global.single_factory;
		GlobalData::Instance = global.global_data;
		GlobalGame::Instance = global.game;
		IdGenerator::Instance = global.id_generator;
	}
}