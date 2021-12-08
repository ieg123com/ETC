#include "StartConfigComponent.h"


namespace Model
{
	StartConfigComponent* StartConfigComponent::Instance = nullptr;


	std::vector<std::shared_ptr<StartConfig>> StartConfigComponent::GetByProcess(const int32_t id)
	{
		std::vector<std::shared_ptr<StartConfig>> result;

		for (auto found_range = __ConfigDict.equal_range(id); found_range.first != found_range.second; ++(found_range.first))
		{
			result.push_back(found_range.first->second);
		}

		return std::move(result);
	}

}