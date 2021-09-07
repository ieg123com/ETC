#include "ActorHandler.h"
#include "module/message/OpcodeTypeComponent.h"


std::shared_ptr<IActorResponse> ActorHandler::__CreateResponseTry(const uint16_t opcode, const int32_t rpc_id, const ETC_ERR error)
{
	auto response = OpcodeTypeComponent::CreateResponseInstanceTry<IActorResponse>(opcode);
	response->SetRpcId(rpc_id);
	response->SetError((int32_t)error);
	return response;
}
