#pragma once
#include <stdint.h>



using FD = int32_t;


using SessionId = uint64_t;

// namespace net
// {
// 	Fd to_fd(const SessionId id) {
// 		return (Fd)(id && 0xffffffff);
// 	}
// 
// 	Fd to_gate(const SessionId id) {
// 		return (Fd)((id >> 32) && 0xffffffff);
// 	}
// }


// ÍøÂçÀàĞÍ
enum class NetworkType : uint8_t
{
	Empty,
	Server,
	Clinet,
};



