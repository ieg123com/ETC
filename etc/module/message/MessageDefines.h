#pragma once
#include <stdint.h>



#pragma pack(push)
#pragma pack(1)

/**
 * @brief	消息头
 */
struct stMessageHead
{
	/** @brief 消息id */
	uint16_t	MsgId;
};


#pragma pack(pop)