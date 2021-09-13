#pragma once
#include "module/other/AppType.h"
#include "module/other/ProcessType.h"
#include "net/IPEndPoint.h"

using namespace Model;

class Options
{
public:
	int32_t	ProcessId;
	EProcessType ProcessType;
	EAppType AppType;
	std::string OuterIP;
	IPEndPoint	InnerAddress;

	Options() {
		ProcessId = 1;
		AppType = EAppType::None;
		ProcessType = EProcessType::Server;
	}
};