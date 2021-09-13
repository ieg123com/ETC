#include "StartProcessConfigComponent.h"



namespace Model
{
	StartProcessConfigComponent* StartProcessConfigComponent::Instance = nullptr;

	std::shared_ptr<StartProcessConfig> StartProcessConfigComponent::Get(const int32_t process_id)const
	{
		auto found = __Dict.find(process_id);
		if (found == __Dict.end())
		{
			throw std::exception(std::format("ÕÒ²»µ½ÅäÖÃ: config name: Config_StartProcess  id: %d", process_id).c_str());
		}
		return found->second;
	}

}