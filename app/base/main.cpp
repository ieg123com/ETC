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
#include "module/message/OpcodeTypeComponent.h"
#include "module/component/OptionComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "module/actor/ActorMessageDispatcherComponent.h"
#include "module/actor/ActorMessageSenderComponent.h"
#include "module/other/SystemEventType.h"
#include "etc/common/timer/TimerComponent.h"


#include "demo/handler/Test.h"



using namespace Model;





int main(int argc,char* argv[])
{


	go [=]{
		Model::Init(argc,argv);
	{
		//Model::Hotfix hotfix;
		try
		{
			//hotfix.Load("hotfix.dll");
			//hotfix.Init(Model::GetGlobalVar());

			LOG_INFO("==============================");
			Game::World()->AddComponent<ConfigComponent>();
			Config_Init::Init();

			
			auto start_config = Game::World()->AddComponent<StartConfigComponent, int32_t>(Game::Options().AppId)->startConfig;
			if (!Is(Game::Options().AppType, start_config->AppType))
			{
				throw std::exception("命令行参数 AppType 和配置中的不一致");
			}

			
			Game::Event().Run<SystemEvent::AppStart&>(SystemEvent::AppStart());



			Game::World()->AddComponent<TimerComponent>();

			switch (start_config->AppType)
			{
			case EAppType::Gate:
				Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>(start_config->OuterAddress);
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Login:
				Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>(start_config->OuterAddress);
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				Game::World()->AddComponent<ActorMessageDispatcherComponent>();
				Game::World()->AddComponent<ActorMessageSenderComponent>();

				break;
			case EAppType::List:
				break;
			case EAppType::Map:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Location:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Chat:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::Social:
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				break;
			case EAppType::AllServer:
				// Net
				Game::World()->AddComponent<NetOuterComponent, const IPEndPoint&>(start_config->OuterAddress);
				Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(start_config->InnerAddress);
				
				
				// 消息分发
				Game::World()->AddComponent<OpcodeTypeComponent>();
				Game::World()->AddComponent<MessageDispatcherComponent>();
				Game::World()->AddComponent<ActorMessageDispatcherComponent>();
				Game::World()->AddComponent<ActorMessageSenderComponent>();


				break;
			default:
				throw std::exception("命令行参数 AppType 不正确");
				break;
			}

			TimerComponent::Instance->RegisterOnceTimer(1000, ::Hotfix::StartTest);
			TimerComponent::Instance->RegisterRepeatedTimer(500, [] {LOG_INFO("wait"); });

			co::CoMutex lock;
			TimerComponent::Instance->RegisterRepeatedTimer(1000, [&] {
				LOG_INFO("start timer");
				lock.lock();
				co_sleep(10000);
				lock.unlock();
				LOG_INFO("over timer");

				});


			LOG_INFO("》》》》》》启动成功");
			while (true)
			{
				try {
					Model::Game::Event().Update();
					Model::Game::Event().LateUpdate();
					co_sleep(50);
				}
				catch (std::exception& e)
				{
					LOG_ERROR("更新时出错 {}", e.what());
				}
				catch (...)
				{
					LOG_ERROR("更新时发生未知错误");
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
			LOG_ERROR("启动服务时发生位置错误，请检查配置是否正确！");
		}
	


	}

	};


	co_sched.Start();
	return 0;
}