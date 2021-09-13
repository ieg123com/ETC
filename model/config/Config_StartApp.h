#pragma once
#include "config/Config.h"


class Config_StartApp:
	public Config
{
public:

	// 所属进程
	int32_t	Process;

	// 所属区
	int32_t	Zone;

	// 类型
	std::string	AppType;

	// 名字
	std::string	Name;

	// 外网端口
	int32_t	OuterPort;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"Process",Process);
		cJSON_Get(json,"Zone",Zone);
		cJSON_Get(json,"AppType",AppType);
		cJSON_Get(json,"Name",Name);
		cJSON_Get(json,"OuterPort",OuterPort);
		return true;
	}
};
