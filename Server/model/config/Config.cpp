#include "Config.h"


namespace Model
{
	ConfigComponent* ConfigComponent::Instance = nullptr;


	class ConfigComponentLoadSystem : public LoadSystem<ConfigComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ConfigComponent>& self) override
		{
			LOG_INFO("Model ConfigComponent Load");
			ConfigComponent::Instance = self.get();
		}
	};
	REF(ConfigComponentLoadSystem, ObjectSystem);

}