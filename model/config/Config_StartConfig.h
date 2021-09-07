#pragma once
#include "config/Config.h"


class Config_StartConfig:
	public Config
{
public:

	// 类型
	std::string	AppType;

	// 外网地址
	std::string	OuterAddress;

	// 内网地址
	std::string	InnerAddress;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"AppType",AppType);
		cJSON_Get(json,"OuterAddress",OuterAddress);
		cJSON_Get(json,"InnerAddress",InnerAddress);
		return true;
	}
};
