#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"
#include "config/Config.h"
#include "config/Config_Init.h"
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
			LOG_INFO("==============================");
			hotfix.Load("hotfix.dll");
			hotfix.Init(Model::GetGlobalVar());
			LOG_INFO("A");
			Game::World()->AddComponent<ConfigComponent>();
			printf("%p\n", ConfigComponent::Instance);
			Config_Init::Init();

			LOG_INFO("B");
			Options option = Game::World()->AddComponent<OptionComponent, int, char* []>(argc, argv)->Options;
			auto start_config = Game::World()->AddComponent<StartConfigComponent, int32_t>(option.AppId)->startConfig;
			LOG_INFO("C");
			if (!Is(option.AppType, start_config->AppType))
			{
				throw std::exception("命令行参数 AppType 和配置中的不一致");
			}


			auto outer_config = start_config->GetComponent<OuterConfig>();
			auto inner_config = start_config->GetComponent<InnerConfig>();


			switch (start_config->AppType)
			{
			case EAppType::Gate:
				Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>(outer_config->Address);
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				break;
			case EAppType::Login:
				break;
			case EAppType::List:
				break;
			case EAppType::Map:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				break;
			case EAppType::Location:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				break;
			case EAppType::Chat:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				break;
			case EAppType::Social:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				break;
			default:
				throw std::exception("命令行参数 AppType 不正确");
				break;
			}


		
			
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