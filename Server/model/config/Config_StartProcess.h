#pragma once
#include "config/Config.h"


class Config_StartProcess:
	public Config
{
public:

	// 进程类型
	std::string	ProcessType;

	// 外网地址
	std::string	OuterIP;

	// 内网地址
	std::string	InnerIP;

	// 内网端口
	int32_t	InnerPort;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"ProcessType",ProcessType);
		cJSON_Get(json,"OuterIP",OuterIP);
		cJSON_Get(json,"InnerIP",InnerIP);
		cJSON_Get(json,"InnerPort",InnerPort);
		return true;
	}
};
