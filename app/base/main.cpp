#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"
#include "config/Config.h"
#include "config/Config_Init.h"
#include "module/message/NetInnerComponent.h"
#include "module/message/NetOuterComponent.h"
#include "module/message/MessageDispatcherComponent.h"
#include "module/component/OptionComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "module/component/config/InnerConfig.h"
#include "module/component/config/OuterConfig.h"



using namespace Model;

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



int main(int argc,char* argv[])
{


	go [=]{
		Model::Init();
	{
		//Model::Hotfix hotfix;
		try
		{
			LOG_INFO("==============================");
			//hotfix.Load("hotfix.dll");
			//hotfix.Init(Model::GetGlobalVar());

			ParseArguments(argc, argv);
			LOG_INFO("A");
			Game::World()->AddComponent<ConfigComponent>();
			printf("%p\n", ConfigComponent::Instance);
			Config_Init::Init();

			LOG_INFO("B");
			
			//Options option = Game::World()->AddComponent<OptionComponent, int, char* []>(argc, argv)->Options;
			auto start_config = Game::World()->AddComponent<StartConfigComponent, int32_t>(Game::Options().AppId)->startConfig;
			LOG_INFO("C");
			if (!Is(Game::Options().AppType, start_config->AppType))
			{
				throw std::exception("�����в��� AppType �������еĲ�һ��");
			}


			auto outer_config = start_config->GetComponent<OuterConfig>();
			auto inner_config = start_config->GetComponent<InnerConfig>();

			LOG_INFO("D");

			switch (start_config->AppType)
			{
			case EAppType::Gate:
				Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>(outer_config->Address);
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Login:
				break;
			case EAppType::List:
				break;
			case EAppType::Map:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Location:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Chat:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Social:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(inner_config->Address);
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			default:
				throw std::exception("�����в��� AppType ����ȷ");
				break;
			}

			LOG_INFO("E");

			while (true)
			{
				try {
					Model::Game::Event().Update();
					Model::Game::Event().LateUpdate();
					co_sleep(100);
				}
				catch (std::exception& e)
				{
					LOG_ERROR("����ʱ���� {}", e.what());
				}
			}
			
		}
		catch (std::exception& e)
		{
			LOG_ERROR("{}", e.what());
			return;
		}
		catch (...)
		{
			LOG_ERROR("��������ʱ����λ�ô������������Ƿ���ȷ��");
		}
	


	}

	};


	co_sched.Start();
	return 0;
}