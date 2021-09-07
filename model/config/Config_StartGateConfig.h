#pragma once
#include "config/Config.h"


class Config_StartGateConfig:
	public Config
{
public:

	// 进程id
	int32_t	Process;

	// 游戏大区
	int32_t	Zone;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"Process",Process);
		cJSON_Get(json,"Zone",Zone);
		return true;
	}
};
