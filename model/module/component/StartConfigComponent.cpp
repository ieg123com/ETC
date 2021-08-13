#include "StartConfigComponent.h"


namespace Model
{
	StartConfigComponent* StartConfigComponent::Instance = nullptr;


	std::shared_ptr<StartConfig> StartConfigComponent::Get(const int32_t app_id)
	{
		auto found = __ConfigDict.find(app_id);
		if (found == __ConfigDict.end())
		{
			return nullptr;
		}
		return found->second;
	}

}