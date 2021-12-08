#pragma once
#include <stdint.h>

/** @brief 用来查询 Actor 的地址 */
using ActorID = uint64_t;

/** 
 * @brief Actor 所在的地址。( 2个字节服务器id + 4个字节时间 + 2个字节递增)
 */
using LocationID = uint64_t;






#pragma pack(push)
#pragma pack(1)

// /**
//  * @brief	Actor 消息头,内部通信使用
//  */
// struct stActorMessageHead
// {
// 	stMessageHead	MessageHead;
// 	ActorID			ActorId;
// 	LocationID		LocationId;
// };
// 




#pragma pack(pop)

