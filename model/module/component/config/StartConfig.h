#pragma once
#include "etc/etc.h"


namespace Model
{
	// ��������
	class StartConfig :
		public GEntity
	{
	public:
		int32_t	AppId;
		int32_t AppType;
	};


}