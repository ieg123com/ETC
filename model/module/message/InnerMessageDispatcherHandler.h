#pragma once
#include <stdint.h>
#include <memory>

namespace Model
{
	class Session;
}

class InnerMessageDispatcherHandler
{
public:

	static void HandleIMActor(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len,FMPReply reply);

	static void HandleIMActorRequest(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len, FMPReply reply);
	
	static void HandleIMActorResponse(const uint16_t opcode, const int32_t actor_id, const char* data, const size_t len);



};