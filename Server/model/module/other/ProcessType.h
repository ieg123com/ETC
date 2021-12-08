#pragma once
#include <stdint.h>
#include <string>

namespace Model
{
	enum class EProcessType : uint32_t
	{
		None = 0,
		Server = 1 << 0,
		Robot = 1 << 1,


	};

	EProcessType ToProcessType(const std::string& str);
	std::string ToString(const EProcessType tp);

	bool Is(const EProcessType a, const EProcessType b);
}