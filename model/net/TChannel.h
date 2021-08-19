#pragma once
#include "coroutine.h"
#include "IChannel.h"
#include "module/memory/MemorySplit.h"
#include <string>


namespace Model
{
	class TChannel:
		public IChannel
	{
	public:

		virtual void OnRead(const char* data, const size_t len)override;

		virtual void Send(const char* data, const size_t len)override;

		virtual void Start()override;

		void Destroy();

	private:




	private:


		co::Channel<std::function<void()>>	m_channel;

		MemorySplit	m_memory_split;
		CircularBuffer m_send_buffer;
		// 即将发送的数据
		std::string	m_send_data;
	};
}

