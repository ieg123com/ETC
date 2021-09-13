#include "StartConfig.h"
#include "config/Config_StartApp.h"
#include "kernel/IdGenerator.h"
#include "module/component/StartProcessConfigComponent.h"



void StartConfig::Init(const std::shared_ptr<Config_StartApp>& config)
{
	AppId = config->Id;
	ProcessId = config->Process;
	ZoneId = config->Zone;
	AppType = ToAppType(config->AppType);
	auto process_config = StartProcessConfigComponent::Instance->Get(ProcessId);
	OuterAddress = IPEndPoint(process_config->OuterIP, config->OuterPort);
	InnerAddress = process_config->InnerAddress;
	InstanceId = InstanceIdStruct(ProcessId,AppId).ToLong();
}