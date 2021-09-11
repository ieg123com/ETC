#pragma once
#include <stdint.h>


// ����ڲ�������Ϣ
enum class ETC_ERR : int32_t
{
	// �쳣�׳���Ϣ 100000+

	NotFoundActor = 150000,

	ActorNoMailBoxComponent = 160000,
	ActorTimeout			= 160001,
	ActorLocationSenderTimeout = 160002,
	ActorLocationSenderTimeout2 = 160003,
	ActorLocationSenderTimeout3 = 160004,





	HandleRpcMessageException	= 170000,
	HandleActorMessageException = 170001,
	HandleActorRpcMessageException = 170002,


};


inline bool IsRpcNeedThrowException(const ETC_ERR error)
{
	if ((int32_t)error > 200000)
	{
		return false;
	}
	return true;
}

