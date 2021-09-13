#pragma once
#include "etc/etc.h"
#include "config/StartProcessConfig.h"



namespace Model
{
	class StartProcessConfigComponent :
		public Component
	{
	public:
		static StartProcessConfigComponent* Instance;

		std::unordered_map<int32_t, std::shared_ptr<StartProcessConfig>>	__Dict;
		std::shared_ptr<StartProcessConfig> Get(const int32_t process_id)const;



	};



}
