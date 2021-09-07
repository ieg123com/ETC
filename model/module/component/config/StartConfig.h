#pragma once
#include <memory>
#include "module/other/AppType.h"
#include "net/IPEndPoint.h"

class Config_StartConfig;

using namespace Model;

// 基础配置
class StartConfig
{
public:
	// 进程id
	int32_t	AppId;
	// 进程类型
	EAppType AppType;
	// 外网地址
	IPEndPoint OuterAddress;
	// 内网地址
	IPEndPoint InnerAddress;

	void Init(const std::shared_ptr<Config_StartConfig>& config);
};
