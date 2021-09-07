#pragma once
#include "etc/etc.h"

class ActorMessageSender;

class ActorLocationSenderComponent:
	public Component
{
	const time_t OUTTIME_TIME = 40 * 1000;

	int32_t m_rpc_id;

	std::map<int32_t, std::shared_ptr<ActorMessageSender>>  m_request_callback;

	// 超时的 ActorMessageSender RpcId
	std::vector<int32_t>	m_timeout_actor_message;
public:
	static ActorLocationSenderComponent* Instance;

	void Check();

	// 发送一条没有回调的消息，可能会出现对方没收到的情况
	void Send(const int64_t actor_id, const std::shared_ptr<IActorMessage>& message);

	// 发送一条消息
	template<typename T>
	std::shared_ptr<T> Call(const int64_t actor_id, const std::shared_ptr<IActorRequest>& request) {
		if (actor_id == 0)
			throw std::exception(std::format("actor id is 0 : %s", request->GetTypeName().c_str()).c_str());
		int32_t rpc_id = __GetRpcId();
		request->SetRpcId(rpc_id);
		return std::static_pointer_cast<T>(__Call(actor_id, rpc_id, request));
	}


private:

	// ActorMessage 消息调用
	std::shared_ptr<IActorResponse> __Call(const int64_t actor_id, const int32_t rpc_id, const std::shared_ptr<IMessage>& message);


	void __Send(const int64_t actor_id, const std::shared_ptr<IMessage>& message);

	void __Run(const std::shared_ptr<ActorMessageSender>& actor_message,const std::shared_ptr<IActorResponse>& response);


	int32_t __GetRpcId();


};



inline int32_t ActorLocationSenderComponent::__GetRpcId() {
	return (++m_rpc_id);
}