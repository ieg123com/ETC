#include "ActorMessageDispatcherComponent.h"


ActorMessageDispatcherComponent* ActorMessageDispatcherComponent::Instance = nullptr;


void ActorMessageDispatcherComponent::Awake()
{
	m_mactor_handler.resize(UINT16_MAX + 1);
	m_mactor_rpc_handler.resize(UINT16_MAX + 1);
}

void ActorMessageDispatcherComponent::Clear()
{
	for (auto& item : m_mactor_handler)item.reset();
	for (auto& item : m_mactor_rpc_handler)item.reset();
}

void ActorMessageDispatcherComponent::RegisterMessage(const uint16_t opcode, const std::shared_ptr<IMSystemHandler>& handler)
{
	// IMActorLocationHandler IMActorLocationRpcHandler 不需要特殊处理，把这个两个当成 Actor 消息正常处理就可以了
	if (auto instance = std::dynamic_pointer_cast<IMActorHandler>(handler))
	{
		m_mactor_handler[opcode] = instance;
	}
	else if (auto instance = std::dynamic_pointer_cast<IMActorRpcHandler>(handler))
	{
		m_mactor_rpc_handler[opcode] = instance;
	}
}

std::shared_ptr<IActorResponse> ActorMessageDispatcherComponent::__Call(const int64_t actor_id, const int32_t rpc_id, const std::shared_ptr<IMessage>& message)
{

}