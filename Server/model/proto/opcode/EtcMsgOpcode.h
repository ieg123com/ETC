#pragma once
#include <stdint.h>


namespace Model
{
	namespace EtcMsgOpcode
	{
		static const uint16_t ActorRequest = 65534;
		static const uint16_t ActorResponse = 65535;

		static const uint16_t A2L_ObjectAddRequest = 100;
		static const uint16_t L2A_ObjectAddResponse = 101;
		static const uint16_t A2L_ObjectLockRequest = 102;
		static const uint16_t L2A_ObjectLockResponse = 103;
		static const uint16_t A2L_ObjectUnLockRequest = 104;
		static const uint16_t L2A_ObjectUnLockResponse = 105;
		static const uint16_t A2L_ObjectRemoveRequest = 106;
		static const uint16_t L2A_ObjectRemoveResponse = 107;
		static const uint16_t A2L_ObjectGetRequest = 108;
		static const uint16_t L2A_ObjectGetResponse = 109;
	}
}