#include "Config.h"



namespace Model
{
	class ConfigComponentLoadSystem : public LoadSystem<ConfigComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<ConfigComponent>& self) override
		{
			ConfigComponent::Instance = self.get();
		}
	};
	REF(ConfigComponentLoadSystem, ObjectSystem);
}