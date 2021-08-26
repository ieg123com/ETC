#pragma once


// 消息类型
enum class EMessageType : unsigned char
{
	Message,
	Request,
	Response,
	ActorMessage,
	ActorRequest,
	ActorResponse
};