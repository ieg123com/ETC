#pragma once
#include "etc/etc.h"
#include "AService.h"


namespace Model
{
	// �����߳����
	// ���ڸ���������Ϣ
	class NetThreadComponent :
		public Component
	{
	public:
		using ptr = std::shared_ptr<NetThreadComponent>;
		static NetThreadComponent* Instance;

		std::unordered_set<std::shared_ptr<AService>>	Services;



	};

	
}

