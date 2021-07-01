#pragma once
#include <stdint.h>

// aoi ����
using AOIObjectID = uint64_t;


// ��ǩ����
enum class ETagType : unsigned int
{
	INVALID			= 1 << 31,
	PLAYER			= 1 << 0,	// ���
	MONSTER			= 1 << 1,	// ����
	ITEM			= 1 << 2,	// ��Ʒ
	NPC				= 1 << 3,	// NPC
	PET				= 1 << 4,	// ����
	SUMMON_BEAST	= 1 << 5,	// �ٻ�����
	BOSS			= 1 << 6,	// Boss
	PUPPET			= 1 << 7,	// ���(��ż������)	

	ALL				= 0xFFFFFFFF,	// ȫ��
};


