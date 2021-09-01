#pragma once
#include <iostream>
#include "other/string/str.h"

// µÿ÷∑
class IPEndPoint
{
	friend std::ostream& operator << (std::ostream&, IPEndPoint&);
public:
	std::string	Ip;
	uint16_t	Port;

	IPEndPoint() {
		Ip = "";
		Port = 0;
	}
	IPEndPoint(const uint64_t port) {
		Ip = "";
		Port = port;
	}
	IPEndPoint(const std::string& address) {
		From(address);
	}
	IPEndPoint(const char* address) {
		From(address);
	}
	IPEndPoint(const std::string& ip, const uint16_t port) {
		Ip = ip;
		Port = port;
	}

	IPEndPoint(const IPEndPoint& obj) {
		Ip = obj.Ip;
		Port = obj.Port;
	}

	IPEndPoint(IPEndPoint&& obj) {
		Ip = std::move(obj.Ip);
		Port = obj.Port;
	}

	bool operator == (const IPEndPoint& obj)const noexcept {
		return (Ip == obj.Ip && Port == obj.Port);
	}

	bool operator != (const IPEndPoint& obj)const noexcept {
		return (Ip != obj.Ip || Port != obj.Port);
	}

	IPEndPoint& operator = (IPEndPoint&& obj) {
		Ip = std::move(obj.Ip);
		Port = std::move(obj.Port);
		return*this;
	}

	IPEndPoint& operator = (const IPEndPoint& obj) {
		Ip = obj.Ip;
		Port = obj.Port;
		return*this;
	}

	void From(const std::string& address) {
		clear();
		auto all_str = std::split(address, ":");
		if (all_str.size() < 2)return;
		Ip = all_str[0];
		Port = std::to<uint16_t>(all_str[1]);
	}

	std::string ToString()const {
		return Ip + ":" + std::to_string(Port);
	}

	void clear() {
		Ip = "";
		Port = 0;
	}

};



namespace std
{
	template<>
	struct hash<IPEndPoint>
	{
		size_t operator ()(const IPEndPoint& self)const noexcept
		{
			return hash<decltype(self.Ip)>()(self.Ip) + hash<decltype(self.Port)>()(self.Port);
		}
	};
}
