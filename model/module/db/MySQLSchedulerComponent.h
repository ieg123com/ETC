#pragma once
#include "etc/etc.h"
#include "MySQL.h"



namespace Model
{
	class MysqlSchedulerComponent :
		public Component
	{
	public:
		static MysqlSchedulerComponent* Instance;


	};
}