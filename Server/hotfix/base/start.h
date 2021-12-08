#pragma once
#include <stdio.h>
#include <string>
#include "test.h"
#include "etc.h"
#include "demo/Entity/PlayerEntity.h"
#include "coroutine.h"

using namespace Model;

namespace Hotfix
{

	void Test(const std::string& str) {
		printf("test %s\n", str.c_str());
	}

	void Start()
	{
		printf("Hotfix.dll �������!\n");

		

		printf("TypeID %d\n", Model::GlobalData::TypeIndex());

		
		printf("start create player\n");
		auto player = ObjectFactory::Create<PlayerEntity>();

		player->Uuid = 100;

		Game::Event().Publish<const std::string&>(player, "123");
		

		LOG_INFO("ok");
		player->Dispose();


		
		try {
			
			Game::Event().Publish<const std::string&>( "sss");
			Game::Event().Publish<const std::string&>("sss");
		}
		catch (std::exception& e)
		{
			LOG_ERROR("{}", e.what());
		}
		catch (...)
		{
			LOG_ERROR("δ֪����");
		}
		printf("Ok\n");

		go[]{
				while (true)
				{
					co_sleep(2000);
					LOG_INFO("Hotfix sleep 1");
				}
		};

		go[]{
		while (true)
		{
			co_sleep(2000);
			LOG_INFO("Hotfix sleep 2");
		}
		};
		LOG_INFO("co_sched.Start()");
		//co_sched.Start();
		LOG_INFO("co_sched.Start() End");
	}

	void Over()
	{
		printf("Hotfix.dll �ر�!\n");

	}
}