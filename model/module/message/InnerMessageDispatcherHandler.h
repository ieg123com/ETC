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

	static void HandleIActorMessage(const int32_t actor_id, const std::shared_ptr<IActorMessage>& message, FMPReply& reply);

	static void HandleIActorRequest(const int32_t actor_id, const std::shared_ptr<IActorRequest>& request, FMPReply& reply);
	
	static void HandleIActorResponse(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len);

	static void FailResponse(const uint16_t opcode, const ETC_ERR error, FMPReply& reply);


};