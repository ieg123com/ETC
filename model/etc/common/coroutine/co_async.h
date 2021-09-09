#pragma once
#include "coroutine.h"
#include "async/async++.h"


namespace co
{
	template<typename Function>
	inline std::result_of_t<std::decay_t<Function>()>
		await(Function&& func)
	{
		auto atask = ::async::spawn(func);
		while (!atask.ready())
		{
			if (co::GetCurrentCoroID() != 0)
				//co_yield;
				std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
		return atask.get();
	}
}
