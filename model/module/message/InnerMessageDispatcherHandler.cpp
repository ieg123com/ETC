#include "InnerMessageDispatcherHandler.h"
#include "OpcodeTypeComponent.h"
#include "module/actor/MailBoxComponent.h"
#include "module/actor/ActorMessageDispatcherComponent.h"
#include "module/actor/ActorMessageSenderComponent.h"
#include "proto/EtcMsg.pb.h"

void InnerMessageDispatcherHandler::HandleIActorMessage(const int64_t actor_id, const std::shared_ptr<IActorMessage>& message)
{
	std::shared_ptr<GEntity> entity;
	if (auto obj = Game::Event().GetObject(actor_id))
	{
		entity = obj->Get<GEntity>();
	}
	if (entity == nullptr)
	{
		// 没有找到acotr
		LOG_ERROR("not found actor: {} {}",
			actor_id,
			message->GetType().full_name());
		return;
	}
	auto mailbox_componet = entity->GetComponent<MailBoxComponent>();
	if (mailbox_componet == nullptr)
	{
		// Actor中没有MailBoxComponent
		LOG_ERROR("actor not add MailBoxComponent : {} {}",
			entity->GetObjectType().GetName(),
			message->GetType().full_name());
		return;
	}

	switch (mailbox_componet->MailBoxType)
	{
	case MailBoxType::MessageDispatcher:
	case MailBoxType::UnorderedMessageDispatcher:
		ActorMessageDispatcherComponent::Instance->Handle(entity, message->GetOpcode(), message.get(), nullptr);
		break;
	case MailBoxType::GateSession:
		// 需要转发给客户端的消息


		break;
	}



}

void InnerMessageDispatcherHandler::HandleIActorRequest(const int64_t actor_id, const std::shared_ptr<IActorRequest>& request, const FMPReply& reply)
{
	std::shared_ptr<GEntity> entity;
	if (auto obj = Game::Event().GetObject(actor_id))
	{
		entity = obj->Get<GEntity>();
	}
	if (entity == nullptr)
	{
		// 没有找到acotr
		FailResponse(request->GetOpcode(), ETC_ERR::NotFoundActor, reply);
		return;
	}
	auto mailbox_componet = entity->GetComponent<MailBoxComponent>();
	if (mailbox_componet == nullptr)
	{
		// Actor中没有MailBoxComponent
		FailResponse(request->GetOpcode(), ETC_ERR::ActorNoMailBoxComponent, reply);
		return;
	}


	switch (mailbox_componet->MailBoxType)
	{
	case MailBoxType::MessageDispatcher:
	case MailBoxType::UnorderedMessageDispatcher:
		ActorMessageDispatcherComponent::Instance->Handle(entity, request->GetOpcode(), request.get(), reply);
		break;
	case MailBoxType::GateSession:
		// 需要转发给客户端的消息


		break;
	}
}

void InnerMessageDispatcherHandler::HandleIActorResponse(const int64_t actor_id, const std::shared_ptr<IActorResponse>& response)
{
	ActorMessageSenderComponent::Instance->RunMessage(actor_id, response);
}

void InnerMessageDispatcherHandler::FailResponse(const uint16_t opcode, const ETC_ERR error, const FMPReply& reply)
{
	auto message = OpcodeTypeComponent::Instance->CreateResponseInstanceTry(opcode);
	if (auto response = dynamic_cast<IResponse*>(message.get()))
	{
		response->SetError((int32_t)error);
		reply(response);
	}
	else {
		throw std::exception(std::format("回复Actor消息时发生错误，回复消息不是IResponse，opcode = %u", opcode).c_str());
	}
}
