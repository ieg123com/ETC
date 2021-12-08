#pragma once
#include <memory>
#include "module/other/AppType.h"
#include "net/IPEndPoint.h"

class Config_StartApp;

using namespace Model;

// 基础配置
class StartConfig
{
public:
	int64_t InstanceId;
	// 进程id
	int32_t	ProcessId;
	// 所在大区id
	int32_t ZoneId;
	// AppId
	int32_t AppId;
	// 进程类型
	EAppType AppType;
	// 外网地址
	IPEndPoint OuterAddress;
	// 内网地址
	IPEndPoint InnerAddress;

	void Init(const std::shared_ptr<Config_StartApp>& config);
};
