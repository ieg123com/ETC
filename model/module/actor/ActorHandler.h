#pragma once
#include <memory>
#include "module/message/MessageDefines.h"
#include "etc/etc_err.h"


class ActorHandler
{
public:
	template<typename T>
	static std::shared_ptr<T> CreateResponseTry(const std::shared_ptr<IMessage>& message, const ETC_ERR error) {
		std::shared_ptr<IActorResponse> actor_req;
		switch (message->GetMessageType())
		{
		case EMessageType::IActorMessage:
		case EMessageType::IActorLocationMessage:
		{
			auto request = dynamic_cast<IActorMessage*>(message.get());
			actor_req = __CreateResponseTry(request->GetOpcode(), request->GetRpcId(), error);
			break;
		}
		case EMessageType::IActorRequest:
		case EMessageType::IActorLocationRequest:
		{
			auto request = dynamic_cast<IActorRequest*>(message.get());
			actor_req = __CreateResponseTry(request->GetOpcode(), request->GetRpcId(), error);
			break;
		}
		default:
			throw std::exception(
				std::format(
					"没有找到这个消息的 actor request 类型，%s : %s",
					message->GetType().full_name(), 
					ToString(message->GetMessageType())).c_str());
			break;
		}
		if (auto response = std::dynamic_pointer_cast<T>(actor_req))
			return response;
		throw std::exception(
			std::format(
				"无法转换回复消息类型 %s => %s",
				actor_req->GetType().full_name(),
				typeof(T).full_name()).c_str());
	}

private:

	static std::shared_ptr<IActorResponse> __CreateResponseTry(const uint16_t opcode, const int32_t rpc_id, const ETC_ERR error);
};