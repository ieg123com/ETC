#include "InnerMessageDispatcherHandler.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"
#include "module/actor/MailBoxComponent.h"
#include "proto/EtcMsg.pb.h"

void InnerMessageDispatcherHandler::HandleIActorMessage(const int32_t actor_id, const std::shared_ptr<IActorMessage>& message, FMPReply& reply)
{
	std::shared_ptr<GEntity> entity;
	if (auto obj = Game::Event().GetObject(actor_id))
	{
		entity = obj->Get<GEntity>();
	}
	if (entity == nullptr)
	{
		// û���ҵ�acotr
		FailResponse(message->GetOpcode(), ETC_ERR::NotFoundActor, reply);
		return;
	}
	auto mailbox_componet = entity->GetComponent<MailBoxComponent>();
	if (mailbox_componet == nullptr)
	{
		// Actor��û��MailBoxComponent
		FailResponse(message->GetOpcode(), ETC_ERR::ActorNoMailBoxComponent, reply);
		return;
	}

	auto message_req = OpcodeTypeComponent::Instance->CreateInstanceTry(message->GetOpcode());

	switch (mailbox_componet->MailBoxType)
	{
	case MailBoxType::MessageDispatcher:


		break;
	case MailBoxType::GateSession:
		// ��Ҫת�����ͻ��˵���Ϣ


		break;
	}



}

void InnerMessageDispatcherHandler::HandleIActorRequest(const int32_t actor_id, const std::shared_ptr<IActorRequest>& request, FMPReply& reply)
{

}

void InnerMessageDispatcherHandler::HandleIActorResponse(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len)
{

}

void InnerMessageDispatcherHandler::FailResponse(const uint16_t opcode, const ETC_ERR error, FMPReply& reply)
{
	auto message = OpcodeTypeComponent::Instance->CreateResponseInstanceTry(opcode);
	if (auto response = dynamic_cast<IResponse*>(message.get()))
	{
		response->SetError((int32_t)error);
		reply(response);
	}
	else {
		throw std::exception(std::format("�ظ�Actor��Ϣʱ�������󣬻ظ���Ϣ����IResponse��opcode = %u", opcode).c_str());
	}
}
