#pragma once
#include <stdint.h>



#pragma pack(push)
#pragma pack(1)

/**
 * @brief	��Ϣͷ
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
	/** @brief ��Ϣid */
	uint16_t	MsgId;
};


struct stRpcMessageHead
{
	/** @brief ��Ϣid */
	uint16_t	MsgId;

	int64_t		RpcId;
};


#pragma pack(pop)