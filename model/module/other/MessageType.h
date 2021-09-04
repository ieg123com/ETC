#pragma once


// 消息类型
enum class EMessageType : unsigned char
{
	None,
	IMessage,
	IRequest,
	IResponse,
	IActorMessage,
	IActorRequest,
	IActorResponse,
	IActorLocationMessage,
	IActorLocationRequest,
	IActorLocationResponse,
};


