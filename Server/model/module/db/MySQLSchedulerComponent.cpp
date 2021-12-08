#include "MySQLSchedulerComponent.h"
#include "config/Config_Mysql.h"
#include "net/IPEndPoint.h"

namespace Model
{

	MySQLSchedulerComponent* MySQLSchedulerComponent::Instance = nullptr;


	MySQLSchedulerComponent::MySQLSchedulerComponent()
	{
		mysql_library_init(0, nullptr, nullptr);

	}

	MySQLSchedulerComponent::~MySQLSchedulerComponent()
	{
		mysql_library_end();
		ClearConnectPool();
	}

	void MySQLSchedulerComponent::LoadConnectParams()
	{
		ClearConnectPool();
		__ConnectParams.clear();
		std::map<std::string, std::string>	params;
		auto all_config = ConfigComponent::Instance->GetAllConfig<Config_Mysql>();
		for (auto& item : all_config)
		{
			if (auto config = item.second->To<Config_Mysql>())
			{
				IPEndPoint address = config->Address;
				params["host"] = address.Ip;
				params["port"] = std::to_string(address.Port);
				params["user"] = config->User;
				params["passwd"] = config->Passwd;
				params["dbname"] = config->DBName;
				__ConnectParams[config->Id] = params;
			}
		}
	}

	std::shared_ptr<MySQL> MySQLSchedulerComponent::Get(const int32_t id)
	{
		MySQL* mysql = nullptr;
		auto found_pool = __ConnectPool.find(id);
		if (found_pool != __ConnectPool.end())
		{
			if (found_pool->second.empty())
			{
				mysql = found_pool->second.front();
				found_pool->second.pop();
				// 连接池中有连接
				if (mysql->Ping())
				{
					return std::shared_ptr<MySQL>(mysql, std::bind(&MySQLSchedulerComponent::FreeMysql,
						this, id, std::placeholders::_1));
				}
				// 连接已经断开了
			}
		}
		
		auto found_params = __ConnectParams.find(id);
		if (found_params == __ConnectParams.end())
		{
			return nullptr;
		}
		mysql = new MySQL(found_params->second);

		if (mysql->Connect())
		{
			return std::shared_ptr<MySQL>(mysql, std::bind(&MySQLSchedulerComponent::FreeMysql,
				this, id, std::placeholders::_1));
		}
		delete mysql;
		return nullptr;
	}

	MySQLRes::ptr MySQLSchedulerComponent::Query(const int32_t id, const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		auto res = Query(id, format, ap);
		va_end(ap);
		return nullptr;
		
	}

	MySQLRes::ptr MySQLSchedulerComponent::Query(const int32_t id, const char* format, va_list ap)
	{
		if (auto mysql = Get(id))
		{
			return mysql->Query(format, ap);
		}
		return nullptr;
	}

	MySQLRes::ptr MySQLSchedulerComponent::Query(const int32_t id, const std::string& sql)
	{
		if (auto mysql = Get(id))
		{
			return mysql->Query(sql);
		}
		return nullptr;
	}


	void MySQLSchedulerComponent::FreeMysql(const int32_t id, MySQL* mysql)
	{
		__ConnectPool[id].push(mysql);
	}

	void MySQLSchedulerComponent::ClearConnectPool()
	{
		for (auto& pool : __ConnectPool)
		{
			while (!pool.second.empty())
			{
				MySQL* mysql = pool.second.front();
				pool.second.pop();
				delete mysql;
			}
		}
	}

}