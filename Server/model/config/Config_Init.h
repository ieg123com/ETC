#pragma once
#include "Config_Mysql.h"
#include "Config_StartApp.h"
#include "Config_StartProcess.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance->Load<Config_Mysql>("Conf/Config_Mysql.json")) LOG_WARN("load 'Conf/Config_Mysql.json' configure file failed!");
		if(!ConfigComponent::Instance->Load<Config_StartApp>("Conf/Config_StartApp.json")) LOG_WARN("load 'Conf/Config_StartApp.json' configure file failed!");
		if(!ConfigComponent::Instance->Load<Config_StartProcess>("Conf/Config_StartProcess.json")) LOG_WARN("load 'Conf/Config_StartProcess.json' configure file failed!");
	}
};
