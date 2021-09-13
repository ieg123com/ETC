#pragma once
#include "etc/etc.h"
#include "net/NetDefines.h"

class StartConfig;

namespace Model
{
	

	class StartConfigComponent :
		public Component
	{
	public:

		static StartConfigComponent* Instance;
		// key: process id  values: config
		std::unordered_multimap<int32_t, std::shared_ptr<StartConfig>>	__ConfigDict;

		std::shared_ptr<StartConfig> startConfig;
		std::shared_ptr<StartConfig> LocationConfig;
		std::shared_ptr<StartConfig> LoginConfig;
		std::shared_ptr<StartConfig> ListConfig;
		std::shared_ptr<StartConfig> ChatConfig;
		std::shared_ptr<StartConfig> SocialConfig;
		// key: zone id  value: <key: map id  vlaue: config>
		std::unordered_map<int32_t, std::shared_ptr<StartConfig>> MapConfig;
		// key: zone id  value: config
		std::unordered_map<int32_t, std::shared_ptr<StartConfig>> GateConfig;
		
		


		std::vector<std::shared_ptr<StartConfig>> GetByProcess(const int32_t id);

	};


}

