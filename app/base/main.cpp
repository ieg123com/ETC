#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"
#include "config/Config.h"
#include "module/message/NetInnerComponent.h"
#include "module/message/NetOuterComponent.h"
#include "module/component/OptionComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "module/component/config/InnerConfig.h"
#include "module/component/config/OuterConfig.h"



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
		
			Game::World()->AddComponent<ConfigComponent>();
			Init();

			Options option = Game::World()->AddComponent<OptionComponent, int, char* []>(argc, argv)->Options;
			auto start_config = Game::World()->AddComponent<StartConfigComponent, int32_t>(option.AppId)->startConfig;
			if (!Is(option.AppType, start_config->AppType))
			{
				throw std::exception("命令行参数 AppType 和配置中的不一致");
			}


			auto outer_config = start_config->GetComponent<OuterConfig>();
			auto inner_config = start_config->GetComponent<InnerConfig>();


			switch (start_config->AppType)
			{
			case EAppType::Gate:
				break;
			case EAppType::Login:
				break;
			case EAppType::List:
				break;
			case EAppType::Map:
				break;
			case EAppType::Location:
				break;
			case EAppType::Chat:
				break;
			case EAppType::Social:
				break;
			default:
				throw std::exception("命令行参数 AppType 不正确");
				break;
			}


		
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