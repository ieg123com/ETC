#pragma once
#include "etc/etc.h"
#include "net/NetDefines.h"


namespace Model
{
	class StartConfig;

	class StartConfigComponent :
		public Component
	{
	public:

		static StartConfigComponent* Instance;
		
		std::unordered_map<int32_t, std::shared_ptr<StartConfig>>	__ConfigDict;
		std::unordered_map<int32_t, IPEndPoint>	__InnerAddressDict;

		std::shared_ptr<StartConfig> startConfig;
		std::shared_ptr<StartConfig> LocationConfig;
		std::shared_ptr<StartConfig> LoginConfig;
		std::shared_ptr<StartConfig> ListConfig;
		std::shared_ptr<StartConfig> ChatConfig;
		std::shared_ptr<StartConfig> SocialConfig;
		std::unordered_map<int32_t, std::shared_ptr<StartConfig>> MapConfig;
		std::unordered_map<int32_t, std::shared_ptr<StartConfig>> GateConfig;
		
		


		std::shared_ptr<StartConfig> Get(const int32_t app_id);

	};


}

