#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"


namespace Model
{
	// ª˘¥°≈‰÷√
	class StartConfig :
		public GEntity
	{
	public:
		int32_t	AppId;
		EAppType AppType;
		std::string Config;
	};


}