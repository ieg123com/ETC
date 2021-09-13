#include "model/module/component/StartProcessConfigComponent.h"
#include "config/Config_StartProcess.h"

namespace Hotfix
{
	class StartProcessConfigComponentAwakeSystem : public AwakeSystem<StartProcessConfigComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<StartProcessConfigComponent>& self)override
		{
			auto all_config = ConfigComponent::Instance->GetAllConfig<Config_StartProcess>();
			for (auto& item : all_config)
			{
				if (auto config = item.second->To<Config_StartProcess>())
				{
					auto process_config = std::make_shared<StartProcessConfig>();
					process_config->Init(config);
					self->__Dict.emplace(process_config->ProcessId, process_config);
				}
			}
			auto process_config = self->Get(Game::Options().ProcessId);
			if (Game::Options().ProcessType != process_config->ProcessType)
			{
				throw std::exception("命令行参数 ProcessType 和配置中的不一致");
			}
			Game::Options().OuterIP = process_config->OuterIP;
			Game::Options().InnerAddress = process_config->InnerAddress;
		}
	};
	REF(StartProcessConfigComponentAwakeSystem, ObjectSystem);

	class StartProcessConfigComponentLoadSystem :public LoadSystem<StartProcessConfigComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<StartProcessConfigComponent>& self)override
		{
			StartProcessConfigComponent::Instance = self.get();
		}
	};
	REF(StartProcessConfigComponentLoadSystem, ObjectSystem);



}

