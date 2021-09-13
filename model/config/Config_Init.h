#pragma once
#include "Config_StartApp.h"
#include "Config_StartProcess.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance->Load<Config_StartApp>("conf/Config_StartApp.json")) LOG_WARN("load 'conf/Config_StartApp.json' configure file failed!");
		if(!ConfigComponent::Instance->Load<Config_StartProcess>("conf/Config_StartProcess.json")) LOG_WARN("load 'conf/Config_StartProcess.json' configure file failed!");
	}
};
