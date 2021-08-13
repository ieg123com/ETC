#pragma once
#include "config/Config.h"


class Config_StartConfig:
	public Config
{
public:

	// 类型
	std::string	AppType;

	// 配置
	std::string	Config;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"AppType",AppType);
		cJSON_Get(json,"Config",Config);
		return true;
	}
};
