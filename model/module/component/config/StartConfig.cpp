#include "StartConfig.h"
#include "config/Config_StartConfig.h"
#include "kernel/IdGenerator.h"



void StartConfig::Init(const std::shared_ptr<Config_StartConfig>& config)
{
	AppId = config->Id;
	AppType = ToAppType(config->AppType);
	OuterAddress = config->OuterAddress;
	InnerAddress = config->InnerAddress;
	InstanceIdStruct instance_id_struct;
	instance_id_struct.process = AppId;
	InstanceId = instance_id_struct.ToLong();
}