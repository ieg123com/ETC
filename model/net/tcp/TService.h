#pragma once
#include "net/AService.h"
#include <unordered_set>


namespace Model
{
	class TService :
		public AService
	{
	public:
		// ��Ҫ���͵�channel id
		std::unordered_set<int64_t>		__NeedStartSend;

		AWEpoll* __WEpoll;


	};
}