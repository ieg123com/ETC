#pragma once
#include "net/AService.h"
#include <unordered_set>


namespace Model
{
	class TService :
		public AService
	{
	public:
		// 需要发送的channel id
		std::unordered_set<int64_t>		__NeedStartSend;

		AWEpoll* __WEpoll;


	};
}