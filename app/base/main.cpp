#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"




int main(int argc,char* argv[])
{


	go []{
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
			printf("加载热重载文件出错 %s\n", e.what());
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