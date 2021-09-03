#pragma once
#include <stdint.h>
#include <memory>

namespace Model
{
	class Session;
}

using namespace Model;

class OuterMessageDispatcherHandler
{
public:

	static void HandleIMessage(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len);

	static void HandleIMRequest(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len);

	static void HandleIMActorLocation(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len);
	
	static void HandleIMActorLocationRequest(const std::shared_ptr<Session>& session, const uint16_t opcode, const char* data, const size_t len);

	//static void HandleIMResponse(const uint16_t opcode, const char* data, const size_t len);

};
