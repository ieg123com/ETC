#pragma once


// ��Ϣ����
enum class EMessageType : unsigned char
{
	Message,
	Request,
	Response,
	ActorMessage,
	ActorRequest,
	ActorResponse
};