#include "OuterMessageDispatcher.h"
#include "MessageDispatcherComponent.h"
#include "OpcodeTypeComponent.h"
#include "net/Session.h"



void OuterMessageDispatcher::Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	uint16_t opcode = 0;
	const char* pos = data;
	size_t size = len;
	if (len < sizeof(opcode))
		throw std::exception(std::format("OuterMessageDispatcher 数据解析错误，因为没法确定消息id！(session->Address() = '%s')", session->Address.ToString().c_str()).c_str());

	memcpy(&opcode, data, sizeof(opcode));
	pos += sizeof(opcode);
	size -= sizeof(opcode);
	LOG_WARN("msg id:{}", opcode);

	EMessageType msg_type = OpcodeTypeComponent::Instance->GetMessageType(opcode);
	if (msg_type == EMessageType::None)
	{
		LOG_WARN("收到一条未知消息类型,opcode = {}", opcode);
		return;
	}

	auto proto_msg = OpcodeTypeComponent::Instance->CreateInstanceTry(opcode);

	if (!proto_msg->ParseFromArray(pos, size))
	{
		// 解析失败,无法获取RpcId。因此不对此进行回复
		return;
	}

	switch (msg_type)
	{
	case EMessageType::IMessage:
	case EMessageType::IRequest:
	{
		MessageDispatcherComponent::Instance->Handle(session, opcode, proto_msg.get());
		break;
	}
	case EMessageType::IActorLocationMessage:
	{
		break;
	}
	case EMessageType::IActorLocationRequest:
	{
		// ActorLocation 消息，将收到的消息转发给需要的服务中
		break;
	}
	default:
		break;
	}



}