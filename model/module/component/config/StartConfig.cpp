#include "StartConfig.h"
#include "config/Config_StartConfig.h"



void StartConfig::Init(const std::shared_ptr<Config_StartConfig>& config)
{
	AppId = config->Id;
	AppType = ToAppType(config->AppType);
	OuterAddress = config->OuterAddress;
	InnerAddress = config->InnerAddress;
}