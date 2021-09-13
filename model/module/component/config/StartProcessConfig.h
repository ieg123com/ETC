#pragma once
#include <memory>
#include "module/other/ProcessType.h"
#include "net/IPEndPoint.h"
#include "system/GameDefinition.h"

class Config_StartProcess;

namespace Model
{
	class StartProcessConfig
	{
	public:
		InstanceID InstanceId;
		int32_t	ProcessId;
		EProcessType ProcessType;
		std::string OuterIP;
		IPEndPoint	InnerAddress;

		void Init(const std::shared_ptr<Config_StartProcess>& config);
	};
}
