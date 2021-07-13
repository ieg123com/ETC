#pragma once
#include "Config_Server.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance().Load<Config_Server>("conf/Config_Server.json")) LOG_WARN("load 'conf/Config_Server.json' configure file failed!");
	}
};
