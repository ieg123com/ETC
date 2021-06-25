#pragma once
#include "Skill/Config_Buff.h"


class Config_Init
{
public:

	static void Init(){
		if(!ConfigComponent::Instance().Load<Config_Buff>("conf/Skill/Config_Buff.json")) LOG_WARN("load 'conf/Skill/Config_Buff.json' configure file failed!");
	}
};
