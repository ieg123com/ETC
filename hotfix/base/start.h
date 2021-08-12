#pragma once
#include <stdio.h>
#include <string>
#include "test.h"
#include "etc.h"
#include "demo/Entity/PlayerEntity.h"

using namespace Model;

namespace Hotfix
{

	void Test(const std::string& str) {
		printf("test %s\n", str.c_str());
	}

	void Start()
	{
		printf("Hotfix.dll 加载完成!\n");

		

		printf("TypeID %d\n", Model::GlobalData::TypeIndex());

		
		printf("start create player\n");
		auto player = ObjectFactory::Create<PlayerEntity>();

		player->Uuid = 100;

		Game::Event().Run<const std::string&>(player, "test", "123");
		

		LOG_INFO("ok");
		player->Dispose();


		
		try {
			
			Game::Event().Run<const std::string&>("test", "sss");
			Game::Event().Run("test", "sss");
		}
		catch (std::exception& e)
		{
			LOG_ERROR("{}", e.what());
		}
		catch (...)
		{
			LOG_ERROR("未知错误");
		}
		printf("Ok\n");


	}

	void Over()
	{
		printf("Hotfix.dll 关闭!\n");

	}
}