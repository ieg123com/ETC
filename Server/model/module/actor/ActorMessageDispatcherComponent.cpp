#include "ActorMessageDispatcherComponent.h"
#include "module/message/interface/IMActorHandler.h"



ActorMessageDispatcherComponent* ActorMessageDispatcherComponent::Instance = nullptr;


void ActorMessageDispatcherComponent::Awake()
{
	m_mactor_handler.resize(UINT16_MAX + 1);
}

void ActorMessageDispatcherComponent::Clear()
{
	for (auto& item : m_mactor_handler)item.reset();
}

void ActorMessageDispatcherComponent::RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMActorHandler>& handler)
{
	// IMActorLocationHandler IMActorLocationRpcHandler ����Ҫ���⴦����������������� Actor ��Ϣ���������Ϳ�����
	m_mactor_handler[opcode] = handler;

}

void ActorMessageDispatcherComponent::Handle(const std::shared_ptr<GEntity>& entity, const uint16_t opcode, IMessage* message, const FMPReply& reply)
{
	if (m_mactor_handler[opcode])
	{
		m_mactor_handler[opcode]->Handle(entity, message, reply);
	}
	else {
		throw std::exception(std::format("������Ϣ������������Ϣû�д���ʵ���� message: %s:%d", message->GetType().full_name(), opcode).c_str());
	}
}