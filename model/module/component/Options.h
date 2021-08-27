#pragma once
#include "module/other/AppType.h"

using namespace Model;

class Options
{
public:
	int32_t	AppId;
	EAppType AppType;

	Options() {
		AppId = 0;
		AppType = EAppType::None;
	}
};