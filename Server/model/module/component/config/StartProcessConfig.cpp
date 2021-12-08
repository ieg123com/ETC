#include "StartProcessConfig.h"
#include "config/Config_StartProcess.h"
#include "kernel/IdGenerator.h"


namespace Model
{
	void StartProcessConfig::Init(const std::shared_ptr<Config_StartProcess>& config)
	{
		ProcessId = config->Id;
		ProcessType = ToProcessType(config->ProcessType);
		OuterIP = config->OuterIP;
		InnerAddress = IPEndPoint(config->InnerIP, config->InnerPort);
		InstanceId = InstanceIdStruct(ProcessId, 0).ToLong();
	}
}