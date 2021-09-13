#include "module/component/StartConfigComponent.h"
#include "config/Config_StartApp.h"
#include "module/component/config/StartConfig.h"

using namespace Model;


namespace Hotfix
{

	class StartConfigComponentAwakeSystem : public AwakeSystem<StartConfigComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<StartConfigComponent>& self) override
		{
			auto& all_config = ConfigComponent::Instance->GetAllConfig<Config_StartApp>();
			for (auto& item : all_config)
			{
				if (auto config = item.second->To<Config_StartApp>())
				{
					auto start_config = std::make_shared<StartConfig>();
					start_config->Init(config);
					self->__ConfigDict.insert(std::make_pair(start_config->ProcessId, start_config));
					Game::Options().AppType = EAppType::None;
					if (start_config->ProcessId == Game::Options().ProcessId)
					{
						// 记录进程拥有的服务
						Game::Options().AppType = (EAppType)((uint32_t)(Game::Options().AppType) | (uint32_t)(start_config->AppType));
					}

					if (Is(start_config->AppType, EAppType::Gate))
					{
						self->GateConfig.insert(std::make_pair(start_config->ZoneId, start_config));
					}
					if (Is(start_config->AppType, EAppType::Login))
					{
						self->LoginConfig = start_config;
					}
					if (Is(start_config->AppType, EAppType::List))
					{
						self->ListConfig = start_config;
					}
					if (Is(start_config->AppType, EAppType::Map))
					{
						self->MapConfig.insert(std::make_pair(start_config->ZoneId, start_config));
					}
					if (Is(start_config->AppType, EAppType::Location))
					{
						self->LocationConfig = start_config;
					}
					if (Is(start_config->AppType, EAppType::Chat))
					{
						self->ChatConfig = start_config;
					}
					if (Is(start_config->AppType, EAppType::Social))
					{
						self->SocialConfig = start_config;
					}

				}
			}


		}
	};
	REF(StartConfigComponentAwakeSystem, ObjectSystem);

	class StartConfigComponentLoadSystem : public LoadSystem<StartConfigComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<StartConfigComponent>& self) override
		{
			StartConfigComponent::Instance = self.get();
		}

	};
	REF(StartConfigComponentLoadSystem, ObjectSystem);
}