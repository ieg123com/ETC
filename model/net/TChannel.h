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
		 * @brief	��һ֡��Ҫ���͵�����
		 */
		CircularBuffer m_send_buffer;
		/**
		 * @brief	�Ѿ����ͣ����ִ������Ϣ
		 */
		std::string	m_send_data;
	};
}

