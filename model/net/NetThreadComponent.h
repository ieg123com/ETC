#pragma once
#include "etc/etc.h"
#include "AService.h"


namespace Model
{
	// 网络线程组件
	// 用于更新网络信息
	class NetThreadComponent :
		public Component
	{
	public:
		using ptr = std::shared_ptr<NetThreadComponent>;
		static NetThreadComponent* Instance;

		std::unordered_set<std::shared_ptr<AService>>	Services;



	};

	
}

