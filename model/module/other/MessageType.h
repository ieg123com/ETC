#pragma once


// ��Ϣ����
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


