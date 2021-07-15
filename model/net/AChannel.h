#pragma once
#include "coroutine.h"


namespace Model
{
	class AChannel
	{
	public:





	private:

		co::Channel<std::function<void()>>	m_channel;

	};
}

