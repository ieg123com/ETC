#pragma once
#include <stdint.h>



using SessionID = int32_t;



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




// 网络类型
enum class NetworkType : uint8_t
{
	Server,
	Client,
};



