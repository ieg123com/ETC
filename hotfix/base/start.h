#pragma once
#include <stdio.h>
#include <string>
#include "test.h"
#include "etc.h"
#include "demo/Entity/PlayerEntity.h"

using namespace Model;

namespace Hotfix
{
	class TestAwakeSystem : public AwakeSystem<PlayerEntity>
	{
	public:
		virtual void Awake(std::shared_ptr<PlayerEntity> self) override
		{
			LOG_INFO("TestAwakeSystem PlayerEntity Awake");



		}
	};

	void Start()
	{
		printf("Hotfix.dll 加载完成!\n");

		

		printf("TypeID %d\n", Model::GlobalData::TypeIndex());


		Type ty = typeof(TestAwakeSystem);

		auto obj = TypeFactory::CreateInstance<TestAwakeSystem>(ty);

		auto awake = std::dynamic_pointer_cast<AwakeSystem<PlayerEntity>>(obj);

		

		auto player = ObjectFactory::Create<PlayerEntity>();

		player->Uuid = 100;

		awake->Run(player);
		printf("Ok\n");

	}

	void Over()
	{
		printf("Hotfix.dll 关闭!\n");

	}
}