#pragma once
#include "kernel/Entity.h"
#include "coroutine.h"
#include "etc/etc_err.h"

namespace Model
{
	// ������¼ActorId��
	class ActorLocationSender :
		public GEntity
	{
	public:
		int64_t		ActorId;
		// �����ʱ��
		time_t		LastSendTime;

		ETC_ERR		Error;

		co::CoMutex Lock;
	};
}