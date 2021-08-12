/**
 * @file	Actor.h
 * @author	ieg123
 * @date	2021-06-30
 * @brief	用于内网通信，记录id方便发送
 */
#pragma once
#include "Object.h"
#include "ActorDefines.h"
#include "net/NetDefines.h"


namespace Model
{
	/** @brief Actor 对象，负责进行内网通信 */
	class Actor :
		public Object
	{
	public:
		/** @brief	内网通信id */
		ActorID	ActorId;
		/** @brief	通信地址，通过次地址， */
		IPEndPoint	Address;

		uint32_t	RpcId;








	};
}