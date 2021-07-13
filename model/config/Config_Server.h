#pragma once
#include "config/Config.h"


class Config_Server:
	public Config
{
public:

	// 类型
	std::string	AppType;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"AppType",AppType);
		return true;
	}
};
