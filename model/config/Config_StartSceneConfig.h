#pragma once
#include "config/Config.h"


class Config_StartSceneConfig:
	public Config
{
public:

	// 进程id
	int32_t	Process;

	// 所属区
	int32_t	Zone;

	// 所属线路
	int32_t	Line;

	// 场景类型
	std::string	SceneType;

	// 场景id
	int32_t	SceneId;

private:

	virtual bool Parse(Json json) override {
		cJSON_Get(json,"Id",Id);
		cJSON_Get(json,"Process",Process);
		cJSON_Get(json,"Zone",Zone);
		cJSON_Get(json,"Line",Line);
		cJSON_Get(json,"SceneType",SceneType);
		cJSON_Get(json,"SceneId",SceneId);
		return true;
	}
};
