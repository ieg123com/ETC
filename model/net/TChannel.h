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
		TChannel();

		virtual void OnRead(const char* data, const size_t len)override;

		virtual void Send(const char* data, const size_t len)override;

		virtual void Start()override;

		void Awake();

		void Destroy();

	private:

		void StartSend();


	private:

		std::shared_ptr<Session>	m_session;

		co::Channel<std::function<void()>>	m_channel;

		MemorySplit	m_memory_split;
		CircularBuffer m_send_buffer;
		// 即将发送的数据
		std::string	m_send_data;
	};
}

