#pragma once
#include <string>

namespace Model
{
	enum EAppType
	{
		None = 0,
		Watcher = 1 << 0,
		Gate = 1 << 1,
		Login = 1 << 2,
		List = 1 << 3,
		Map = 1 << 4,
		Location = 1 << 5,
		Chat = 1 << 6,
		Social = 1 << 7,

		Robot = 1<< 20,

		AllServer = Watcher | Gate | Login | List | Map | Location | Chat | Social,
	};

	EAppType ToAppType(const std::string& str);

	bool Is(const EAppType a, const EAppType b);
}