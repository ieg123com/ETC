#pragma once
#include "kernel/Entity.h"
#include "NetDefines.h"
#include "IPEndPoint.h"
#include "module/message/MessageDefines.h"
#include <string>

namespace Model
{
	class AService;

	class Session :
		public GEntity
	{
		// 要发送的数据
		std::string	m_data_sent;
	public:

		int32_t		RpcId;

		IPEndPoint	RemoteAddress;
		/** @brief 网络服务*/
		std::shared_ptr<AService>	__Service;

		/** @brief 发送消息*/
		void Send(const char* data, const size_t len);

		void Send(const uint16_t opcode, const char* data, const size_t len);

		void Send(const int64_t actor_id, const IMessage* message);

		void Send(const IMessage* message);

		void Reply(const IMessage* message);


	public:

		void Awake(const std::shared_ptr<AService>& service);

		void Destroy();
	};
}
