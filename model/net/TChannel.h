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

		void Awake();

		void LateUpdate();

		void Destroy();

	private:

		void __StartSend();


	private:

		std::shared_ptr<Session>	m_session;

		MemorySplit	m_memory_split;

		/**
		 * @brief	下一帧需要发送的数据
		 */
		CircularBuffer m_send_buffer;
		/**
		 * @brief	已经发送，出现错误的消息
		 */
		std::string	m_send_data;
	};
}

