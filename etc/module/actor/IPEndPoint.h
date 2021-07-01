#pragma once
#include <string>


class IPEndPoint
{
public:

	std::string	Ip;
	uint32_t	Port;

	IPEndPoint() {
		Ip = "";
		Port = 0;
	}
};