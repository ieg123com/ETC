#pragma once
#include "kernel/Entity.h"

using namespace Model;

// ������¼ActorId��
class ActorLocationSender:
	public GEntity
{
public:
	int64_t		ActorId;
	// �����ʱ��
	time_t		LastSendTime;

	

};