#pragma once
#include "etc/etc.h"
#include "module/message/MessageDefines.h"

class IMActorHandler;

// Actor ��Ϣ�ַ����
// �ַ� AMActorHandler AMActorRpcHandler AMActorLocationHandler AMActorLocationRpcHandler ��Ϣ
class ActorMessageDispatcherComponent :
	public Component
{

	std::vector<std::shared_ptr<IMActorHandler>>	m_mactor_handler;


public:
	static ActorMessageDispatcherComponent* Instance;


	void Awake();

	void Clear();

	void RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMActorHandler>& handler);


	void Handle(const std::shared_ptr<GEntity>& entity,const uint16_t opcode, IMessage* message, const FMPReply& reply);










};


