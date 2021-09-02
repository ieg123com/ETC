#include "module/component/config/StartConfig.h"
#include "config/Config_StartConfig.h"
#include "module/other/AppType.h"
#include "module/component/config/OuterConfig.h"
#include "module/component/config/InnerConfig.h"
#include "other/json/cJsonHelper.h"


using namespace Model;

namespace Hotfix
{
	class StartConfigAwakeSystem : public AwakeSystem<StartConfig, const std::shared_ptr<Config_StartConfig>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<StartConfig>& self, const std::shared_ptr<Config_StartConfig>& config) override
		{
			self->AppId = config->Id;
			self->AppType = ToAppType(config->AppType);
			self->Config = config->Config;
			cJSON* json = cJSON_Parse(self->Config.c_str());
			if (json == nullptr)return;
			cJSON* new_json = json->child;

			do {
				std::string type_value;
				if (!cJSON_Get(new_json, "Type", type_value))continue;

				if (type_value == "OuterConfig")self->AddComponent<OuterConfig, cJSON*>(new_json);
				else if(type_value == "InnerConfig")self->AddComponent<InnerConfig, cJSON*>(new_json);

			} while (new_json = cJSON_Next(new_json));
			cJSON_Delete(json);
		}

	};
	REF(StartConfigAwakeSystem, ObjectSystem);
}