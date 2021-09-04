#pragma once
#include <stdint.h>


namespace Model
{
	namespace EtcMsgOpcode
	{
		static uint16_t ActorRequest = 65534;
		static uint16_t ActorResponse = 65535;

		static uint16_t MessageHead = 10;
		static uint16_t TestRequest = 19;
		static uint16_t TestResponse = 20;
		static uint16_t ActorTestRequest = 21;
		static uint16_t ActorTestResponse = 22;
		static uint16_t ActorMessageTest = 23;
	}
}