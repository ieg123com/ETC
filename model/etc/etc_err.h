#pragma once
#include <stdint.h>


// ����ڲ�������Ϣ
enum class ETC_ERR : int32_t
{
	// �ڲ�������������Ϣ 100000+

	NotFoundActor = 150000,

	ActorNoMailBoxComponent = 160000,
	ActorTimeout			= 160001,


	HandleRpcMessageException	= 170000,

};


