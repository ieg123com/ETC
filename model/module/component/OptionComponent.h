#pragma once
#include "etc/etc.h"


namespace Model
{
	class Options
	{
	public:
		int32_t	AppId;
		int32_t AppType;
		std::string Config;
	};


	class OptionComponent :
		public Component 
	{
	public:
		Options Options;


	};
}