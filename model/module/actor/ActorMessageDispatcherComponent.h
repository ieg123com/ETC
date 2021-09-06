#pragma once
#include "etc/etc.h"


class ActorMessageDispatcherComponent :
	public Component
{
	std::vector<std::shared_ptr<IMActorHandler>>	m_mactor_handler;
	std::vector<std::shared_ptr<IMActorRpcHandler>>	m_mactor_rpc_handler;
public:
	static ActorMessageDispatcherComponent* Instance;


	void Awake();

	void Clear();

	void RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMSystemHandler>& handler);


	void Handle();





private:

	// ActorMessage 消息调用
	std::shared_ptr<IActorResponse> __Call(const int64_t actor_id, const int32_t rpc_id, const std::shared_ptr<IMessage>& message);







};