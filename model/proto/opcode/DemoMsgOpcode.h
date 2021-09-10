#pragma once
#include <stdint.h>



namespace Model
{
	namespace DemoMsgOpcode
	{
		static const uint16_t MessageHead = 10000;
		static const uint16_t ActorLocationTestRequest = 10002;
		static const uint16_t ActorLocationTestResponse = 10003;
		static const uint16_t ActorLocationMessageTest = 10004;
		static const uint16_t ActorTestRequest = 10005;
		static const uint16_t ActorTestResponse = 10006;
		static const uint16_t ActorMessageTest = 10007;
	}
}