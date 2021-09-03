#include "InnerMessageDispatcherHandler.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"
#include "module/actor/MailBoxComponent.h"
#include "proto/etc_msg.pb.h"

void InnerMessageDispatcherHandler::HandleIActorMessage(const uint16_t opcode, const int32_t actor_id, const PBMessage* request, FMPReply reply)
{
	std::shared_ptr<GEntity> entity;
	if (auto obj = Game::Event().GetObject(actor_id))
	{
		entity = obj->Get<GEntity>();
	}
	if (entity == nullptr)
	{
		// 没有找到acotr
		FailResponse(opcode, ETC_ERR::NotFoundActor, reply);
		return;
	}
	auto mailbox_componet = entity->GetComponent<MailBoxComponent>();
	if (mailbox_componet == nullptr)
	{
		// Actor中没有MailBoxComponent
		FailResponse(opcode, ETC_ERR::ActorNoMailBoxComponent, reply);
		return;
	}

	auto message_req = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);

	switch (mailbox_componet->MailBoxType)
	{
	case MailBoxType::MessageDispatcher:


		break;
	case MailBoxType::GateSession:
		// 需要转发给客户端的消息


		break;
	}



}

void InnerMessageDispatcherHandler::HandleIActorRequest(const uint16_t opcode, const int32_t actor_id, const PBMessage* request, FMPReply reply)
{

}

void InnerMessageDispatcherHandler::HandleIActorResponse(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len)
{

}

void InnerMessageDispatcherHandler::FailResponse(const uint16_t opcode, const ETC_ERR error, FMPReply reply)
{
	uint16_t opcode_rpo = OpcodeTypeComponent::Instance->GetResponseOpcodeTry(opcode);
	auto message_rpo = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode_rpo);
	stIMResponse st_rpo;
	st_rpo.Error = (int32_t)error;
	if (!OpcodeTypeComponent::Instance->ResetMessageResponse(opcode_rpo, message_rpo.get(), st_rpo))
	{
		throw std::exception(std::format("消息回复类型格式不正确,opcode = %d", opcode_rpo).c_str());
	}
	reply(message_rpo.get());
}
