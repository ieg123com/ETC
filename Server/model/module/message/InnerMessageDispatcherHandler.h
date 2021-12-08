#pragma once
#include <stdint.h>
#include <memory>
#include "etc/etc_err.h"
#include "MessageDefines.h"

namespace Model
{
	class Session;
}

class InnerMessageDispatcherHandler
{
public:

	static void HandleIActorMessage(const int64_t actor_id, const std::shared_ptr<IActorMessage>& message);

	static void HandleIActorRequest(const int64_t actor_id, const std::shared_ptr<IActorRequest>& request, const FMPReply& reply);
	
	static void HandleIActorResponse(const int64_t actor_id, const std::shared_ptr<IActorResponse>& response);

	static void FailResponse(const uint16_t opcode, const ETC_ERR error, const FMPReply& reply);


};