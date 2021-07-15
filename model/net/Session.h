#pragma once
#include "etc.h"
#include "NetDefines.h"
#include "module/memory/MemorySplit.h"
#include <string>

namespace Model
{
	class Service;


	class Session :
		public GEntity
	{
		friend class Service;

	public:

		int32_t		RpcId;

		SessionID	SessionId;

		IPEndPoint	Address;
		/** @brief 网络服务*/
		std::shared_ptr<Service>	__service;


		/** @brief 消息到达*/
		void OnRead(const char* data, const size_t len);

		/** @brief 发送消息*/
		void Send(const char* data, const size_t len);

	protected:

		virtual void Awake() override;

		virtual void Destroy() override;


	private:



		//co::Channel<std::function<void()>>	m_channel;

		MemorySplit	m_memory_split;

	};
}