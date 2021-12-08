#pragma once
#include "kernel/Entity.h"
#include "coroutine.h"
#include "etc/etc_err.h"

namespace Model
{
	// 用来记录ActorId的
	class ActorLocationSender :
		public GEntity
	{
	public:
		int64_t		ActorId;
		// 最后发送时间
		time_t		LastSendTime;

		ETC_ERR		Error;

		co::CoMutex Lock;
	};
}