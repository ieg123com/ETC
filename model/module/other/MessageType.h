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

inline const char* ToString(const EMessageType msg_type) {
	switch (msg_type)
	{
	case EMessageType::None: return "None";
	case EMessageType::IMessage: return "IMessage";
	case EMessageType::IRequest: return "IRequest";
	case EMessageType::IResponse: return "IResponse";
	case EMessageType::IActorMessage: return "IActorMessage";
	case EMessageType::IActorRequest: return "IActorRequest";
	case EMessageType::IActorResponse: return "IActorResponse";
	case EMessageType::IActorLocationMessage: return "IActorLocationMessage";
	case EMessageType::IActorLocationRequest: return "IActorLocationRequest";
	case EMessageType::IActorLocationResponse: return "IActorLocationResponse";
	default: return "Unknown";
	}
}


