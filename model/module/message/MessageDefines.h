#pragma once
#include <stdint.h>



#pragma pack(push)
#pragma pack(1)

/**
 * @brief	消息头
 */
class MessageHead
{

};

class RequestMessageHead :
	public MessageHead
{
public:
	int32_t		RpcId;
};

class ResponseMessageHead :
	public MessageHead
{
public:
	int32_t		RpcId;
	int32_t		Error;
};


struct stMessageHead
{
	/** @brief 消息id */
	uint16_t	MsgId;
};


struct stRpcMessageHead
{
	/** @brief 消息id */
	uint16_t	MsgId;

	int64_t		RpcId;
};


#pragma pack(pop)