#pragma once
#include <memory>
#include "module/other/AppType.h"
#include "net/IPEndPoint.h"

class Config_StartConfig;

using namespace Model;

// ��������
class StartConfig
{
public:
	// ����id
	int32_t	AppId;
	// ��������
	EAppType AppType;
	// ������ַ
	IPEndPoint OuterAddress;
	// ������ַ
	IPEndPoint InnerAddress;

	void Init(const std::shared_ptr<Config_StartConfig>& config);
};
