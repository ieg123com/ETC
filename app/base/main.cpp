#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"
#include "module/message/NetInnerComponent.h"
#include "module/message/NetOuterComponent.h"
#include "module/component/OptionComponent.h"


using namespace Model;


int main(int argc,char* argv[])
{


	go [=]{
		Model::Init();
	{
		Model::Hotfix hotfix;
		try
		{
			hotfix.Load("hotfix.dll");
			hotfix.Init(Model::GetGlobalVar());
		}
		catch (std::exception& e)
		{
			LOG_ERROR("加载热重载文件出错 {}", e.what());
			return;
		}

		Game::World()->AddComponent<OptionComponent, int, char*[]>(argc, argv);


		try
		{
			Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>("127.0.0.1:2881");
			Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>("127.0.0.1:1881");
		}
		catch (std::exception& e)
		{
			LOG_ERROR("{}", e.what());
			return;
		}
	




		while (true)
		{
			try {
				Model::Game::Event().Update();
				Model::Game::Event().LateUpdate();
				co_sleep(100);
			}
			catch (std::exception& e)
			{
				LOG_ERROR("更新时出错 {}",e.what());
			}
		}

	}

	};


	co_sched.Start();
	return 0;
}