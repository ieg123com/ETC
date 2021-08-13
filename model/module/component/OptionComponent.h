#pragma once
#include "etc/etc.h"
#include "module/other/AppType.h"

namespace Model
{

	class Options
	{
	public:
		int32_t	AppId;
		EAppType AppType;
	};


	class OptionComponent :
		public Component 
	{
	public:
		Options Options;


	};
}