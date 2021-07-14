#pragma once
#include <stdint.h>
#include "string/str.h"



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


namespace Model
{
	// 地址
	class IPEndPoint
	{
	public:
		std::string	Ip;
		uint16_t	Port;

		IPEndPoint() {
			Ip = "";
			Port = 0;
		}

		IPEndPoint(const std::string& ip,const uint16_t port) {
			Ip = ip;
			Port = port;
		}

		IPEndPoint(IPEndPoint&& obj){
			Ip = std::move(obj.Ip);
			Port = obj.Port;
		}

		bool operator == (const IPEndPoint& obj)const noexcept{
			return (Ip == obj.Ip && Port == obj.Port);
		}

		bool operator != (const IPEndPoint& obj)const noexcept{
			return (Ip != obj.Ip || Port != obj.Port);
		}

		IPEndPoint& operator = (IPEndPoint&& obj){
			Ip = std::move(obj.Ip);
			Port = std::move(obj.Port);
			return* this;
		}

		void From(const std::string& address){
			clear();
			auto all_str = std::split(address, ":");
			if (all_str.size() < 2)return;
			Ip = all_str[0];
			Port = std::to<uint16_t>(all_str[1]);
		}

		std::string ToString()const{
			return Ip + ":" + std::to_string(Port);
		}

		void clear() {
			Ip = "";
			Port = 0;
		}

	};


}

namespace std
{
	template<>
	struct hash<Model::IPEndPoint>
	{
		size_t operator ()(const Model::IPEndPoint& self)const noexcept
		{
			return hash<decltype(self.Ip)>()(self.Ip) + hash<decltype(self.Port)>()(self.Port);
		}
	};
}
