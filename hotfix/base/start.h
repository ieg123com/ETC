#pragma once
#include <stdio.h>
#include <string>
#include "test.h"
#include "etc.h"
#include "demo/Entity/PlayerEntity.h"

using namespace Model;

namespace Hotfix
{

	void Start()
	{
		printf("Hotfix.dll �������!\n");

		

		printf("TypeID %d\n", Model::GlobalData::TypeIndex());

		
		printf("start create player\n");
		auto player = ObjectFactory::Create<PlayerEntity>();

		player->Uuid = 100;

		Game::Event().Run<const std::string&>(player, "test", "123");

		player->Dispose();

		printf("Ok\n");

		Game::Event().Run("test","sss");


	}

	void Over()
	{
		printf("Hotfix.dll �ر�!\n");

	}
}