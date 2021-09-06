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



	


private:







};