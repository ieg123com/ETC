#pragma once
#include <stdint.h>

// aoi 对象
using AOIObjectID = uint64_t;


// 标签类型
enum class ETagType : unsigned int
{
	INVALID			= 1 << 31,
	PLAYER			= 1 << 0,	// 玩家
	MONSTER			= 1 << 1,	// 怪物
	ITEM			= 1 << 2,	// 物品
	NPC				= 1 << 3,	// NPC
	PET				= 1 << 4,	// 宠物
	SUMMON_BEAST	= 1 << 5,	// 召唤怪物
	BOSS			= 1 << 6,	// Boss
	PUPPET			= 1 << 7,	// 马甲(布偶、傀儡)	

	ALL				= 0xFFFFFFFF,	// 全部
};


