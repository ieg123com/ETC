#pragma once
#include <memory>
#include "module/other/AppType.h"
#include "net/IPEndPoint.h"

class Config_StartApp;

using namespace Model;

// ��������
class StartConfig
{
public:
	int64_t InstanceId;
	// ����id
	int32_t	ProcessId;
	// ���ڴ���id
	int32_t ZoneId;
	// AppId
	int32_t AppId;
	// ��������
	EAppType AppType;
	// ������ַ
	IPEndPoint OuterAddress;
	// ������ַ
	IPEndPoint InnerAddress;

	void Init(const std::shared_ptr<Config_StartApp>& config);
};
