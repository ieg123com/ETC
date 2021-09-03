#pragma once
#include <stdint.h>


// 框架内部错误消息
enum class ETC_ERR : int32_t
{
	// 内部处理错误错误消息 100000+

	NotFoundActor = 150000,

	ActorNoMailBoxComponent = 160000,

};


