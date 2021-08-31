#pragma once
#include "kernel/Entity.h"
#include "NetDefines.h"
#include "google/protobuf/message.h"
#include <string>

namespace Model
{
	class IChannel;
	class Service;
	class NetworkComponent;

	class Session :
		public GEntity
	{
		// 要发送的数据
		std::string	m_data_sent;
	public:

		int32_t		RpcId;

		SessionID	SessionId;

		IPEndPoint	Address;
		/** @brief 网络服务*/
		std::shared_ptr<Service>	__service;
		// 数据处理
		std::shared_ptr<IChannel>	__channel;

		std::shared_ptr<NetworkComponent>	__networkcomponent;

		/** @brief 消息到达*/
		void OnRead(const char* data, const size_t len);

		/** @brief 发送消息*/
		void Send(const char* data, const size_t len);

		template<typename T>
		void Reply(const T& message) {
			__Reply(typeof(T), &message);
		}

	public:

		void Awake(const std::shared_ptr<Service>& service);

		void Destroy();


	private:
	
		void __Reply(const Type& tp, const ::google::protobuf::Message* message);
	};
}