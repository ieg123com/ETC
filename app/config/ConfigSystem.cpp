#include "config/Config.h"

using namespace Model;

namespace Hotfix
{
	class ConfigComponentLoadSystem : public LoadSystem<ConfigComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ConfigComponent>& self) override
		{
			LOG_INFO("Hotfix ConfigComponent Load");
			ConfigComponent::Instance = self.get();
		}
	};
	REF(ConfigComponentLoadSystem, ObjectSystem);
}