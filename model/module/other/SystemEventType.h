#pragma once
#include "EventType.h"


namespace Model
{
	// 事件系统事件类型
	enum ESystemEventType
	{
		BEGIN	= EEventType::SYSTEM,
		StartRegMessage,		// 开始注册事件
		StartBindRpcMessage,	// 开始绑定Rpc消息

	};

}
