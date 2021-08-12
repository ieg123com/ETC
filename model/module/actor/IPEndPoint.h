#pragma once
#include "string/str.h"


class IPEndPoint
{
public:

	std::string	Ip;
	uint32_t	Port;

	IPEndPoint() {
		Ip = "";
		Port = 0;
	}

	IPEndPoint(const std::string& ip, const uint32_t port) {
		Ip = ip;
		Port = port;
	}

	IPEndPoint(const std::string& addr) {
		Ip = "";
		Port = 0;

		auto strs = std::split(addr, ":");
		if (strs.size() > 0)
			Ip = strs[0];
		if (strs.size() > 1)
			Port = std::to<uint32_t>(strs[1]);
	}
};