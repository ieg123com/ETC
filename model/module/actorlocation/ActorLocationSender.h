#pragma once
#include "kernel/Entity.h"
#include "etc/etc_err.h"

using namespace Model;

// ������¼ActorId��
class ActorLocationSender:
	public GEntity
{
public:
	int64_t		ActorId;
	// �����ʱ��
	time_t		LastSendTime;

	ETC_ERR		Error;

};