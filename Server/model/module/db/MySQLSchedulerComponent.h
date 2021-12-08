#pragma once
#include "etc/etc.h"
#include "MySQL.h"



namespace Model
{
	class MySQLSchedulerComponent :
		public Component
	{
	public:
		static MySQLSchedulerComponent* Instance;

		// 连接参数
		std::unordered_map<int32_t, std::map<std::string, std::string>>  __ConnectParams;
		// 连接池
		std::unordered_map<int32_t, std::queue<MySQL*>>	__ConnectPool;
			
		MySQLSchedulerComponent();
		~MySQLSchedulerComponent();

		// 加载连接参数
		void LoadConnectParams();

		std::shared_ptr<MySQL> Get(const int32_t id);

		
		MySQLRes::ptr Query(const int32_t id, const char* format, ...);
		MySQLRes::ptr Query(const int32_t id, const char* format, va_list ap);
		MySQLRes::ptr Query(const int32_t id, const std::string& sql);


	private:

		void FreeMysql(const int32_t id,MySQL* mysql);

		void ClearConnectPool();

	};
}