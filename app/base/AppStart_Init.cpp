#include "etc/etc.h"
#include "config/Config.h"
#include "config/Config_Init.h"
#include "model/module/message/NetInnerComponent.h"
#include "model/module/message/NetOuterComponent.h"
#include "model/module/message/MessageDispatcherComponent.h"
#include "model/module/message/OpcodeTypeComponent.h"
#include "model/module/component/OptionComponent.h"
#include "model/module/component/StartConfigComponent.h"
#include "model/module/component/StartProcessConfigComponent.h"
#include "model/module/component/config/StartConfig.h"
#include "model/module/actor/ActorMessageDispatcherComponent.h"
#include "model/module/actor/ActorMessageSenderComponent.h"
#include "model/module/actorlocation/LocationProxyComponent.h"
#include "model/module/actorlocation/ActorLocationSenderComponent.h"
#include "model/module/other/SystemEventType.h"
#include "module/entity/AppFactory.h"



namespace Hotfix
{
	class AppStart_Init :public EventSystem<SystemEvent::AppStart&>
	{
	public:
		virtual void Run(SystemEvent::AppStart& app_start)override
		{
			LOG_INFO("AppStart_Init");
			Game::World()->AddComponent<ConfigComponent>();
			Config_Init::Init();


			Game::World()->AddComponent<TimerComponent>();
			Game::World()->AddComponent<StartProcessConfigComponent>();
			Game::World()->AddComponent<StartConfigComponent>();
			// 监听内网端口
			Game::World()->AddComponent<NetInnerComponent, const IPEndPoint&>(Game::Options().InnerAddress);
			Game::World()->AddComponent<OpcodeTypeComponent>();
			Game::World()->AddComponent<MessageDispatcherComponent>();
			// 发送 actor 消息
			Game::World()->AddComponent<ActorMessageDispatcherComponent>();
			Game::World()->AddComponent<ActorMessageSenderComponent>();
			// 访问 location server 组件的
			Game::World()->AddComponent<LocationProxyComponent>();
			// 发送 actor location 消息
			Game::World()->AddComponent<ActorLocationSenderComponent>();

			switch (Game::Options().ProcessType)
			{
			case EProcessType::Server:
			{
				auto all_config = StartConfigComponent::Instance->GetByProcess(Game::Options().ProcessId);
				for (auto& config : all_config)
				{
					AppFactory::Create(Game::World(), config);
				}
				break;
			}
			default:
				break;
			}



		}
	};
	REF(AppStart_Init, Event);


}