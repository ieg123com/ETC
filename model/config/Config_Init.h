#pragma once
#include "Config_StartConfig.h"
#include "Config_StartGateConfig.h"
#include "Config_StartSceneConfig.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance->Load<Config_StartConfig>("conf/Config_StartConfig.json")) LOG_WARN("load 'conf/Config_StartConfig.json' configure file failed!");
		if(!ConfigComponent::Instance->Load<Config_StartGateConfig>("conf/Config_StartGateConfig.json")) LOG_WARN("load 'conf/Config_StartGateConfig.json' configure file failed!");
		if(!ConfigComponent::Instance->Load<Config_StartSceneConfig>("conf/Config_StartSceneConfig.json")) LOG_WARN("load 'conf/Config_StartSceneConfig.json' configure file failed!");
	}
};
