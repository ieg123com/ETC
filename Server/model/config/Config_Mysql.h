#pragma once
#include "config/Config.h"


class Config_Mysql:
	public Config
{
public:

	// 地址
	std::string	Address;

	// 用户名
	std::string	User;

	// 密码
	std::string	Passwd;

	// 数据库名
	std::string	DBName;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"Address",Address);
		cJSON_Get(json,"User",User);
		cJSON_Get(json,"Passwd",Passwd);
		cJSON_Get(json,"DBName",DBName);
		return true;
	}
};
