#include "module/component/StartConfigComponent.h"
#include "config/Config_StartConfig.h"
#include "module/component/config/StartConfig.h"
#include "module/component/config/InnerConfig.h"

using namespace Model;


namespace Hotfix
{

	class StartConfigComponentAwakeSystem : public AwakeSystem<StartConfigComponent,int32_t>
	{
	public:
		virtual void Awake(const std::shared_ptr<StartConfigComponent>& self,int32_t app_id) override
		{
			auto& all_config = ConfigComponent::Instance->GetAllConfig<Config_StartConfig>();

			for (auto& item : all_config)
			{
				if (auto config = item.second->To<Config_StartConfig>())
				{
					auto start_config = ObjectFactory::Create<StartConfig, const std::shared_ptr<Config_StartConfig>&>(config);
					self->__ConfigDict.insert(std::make_pair(start_config->AppId, start_config));
					
					if (auto inner_config = start_config->GetComponent<InnerConfig>())
					{
						self->__InnerAddressDict.insert(std::make_pair(start_config->AppId, inner_config->Address));
					}

					if (Is(start_config->AppType, EAppType::Gate))
					{
						self->GateConfig.insert(std::make_pair(start_config->AppId, start_config));
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
						self->MapConfig.insert(std::make_pair(start_config->AppId, start_config));
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

			self->startConfig = self->Get(app_id);

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