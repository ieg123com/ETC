#pragma once
#include <stdint.h>

namespace Model
{
	using SessionID = int32_t;







	// 网络类型
	enum class NetworkType : uint8_t
	{
		Server,
		Client,
	};

}



