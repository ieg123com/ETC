#pragma once
#include <stdint.h>


// 框架内部错误消息
enum class ETC_ERR : int32_t
{
	// 异常抛出消息 100000+

	NotFoundActor = 150000,

	ActorNoMailBoxComponent = 160000,
	ActorTimeout			= 160001,


	HandleRpcMessageException	= 170000,

};


inline bool IsRpcNeedThrowException(const ETC_ERR error)
{
	if ((int32_t)error > 200000)
	{
		return false;
	}
	return true;
}

