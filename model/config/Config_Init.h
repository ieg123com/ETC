#pragma once
#include "Config_StartConfig.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance->Load<Config_StartConfig>("conf/Config_StartConfig.json")) LOG_WARN("load 'conf/Config_StartConfig.json' configure file failed!");
	}
};
