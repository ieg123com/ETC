#pragma once
#include "etc.h"
#include "NetDefines.h"
#include <string>

namespace Model
{
	class IChannel;
	class Service;

	class Session :
		public GEntity
	{
	public:

		int32_t		RpcId;

		SessionID	SessionId;

		IPEndPoint	Address;
		/** @brief 网络服务*/
		std::shared_ptr<Service>	__service;
		// 数据处理
		std::shared_ptr<IChannel>	__channel;

		/** @brief 消息到达*/
		void OnRead(const char* data, const size_t len);

		/** @brief 发送消息*/
		void Send(const char* data, const size_t len);

	public:

		void Awake(const std::shared_ptr<Service>& service);

		void Destroy();


	private:


	};
}