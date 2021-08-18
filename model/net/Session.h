#pragma once
#include "etc.h"
#include "NetDefines.h"
#include <string>

namespace Model
{
	class IChannel;

	class Session :
		public GEntity
	{
	public:

		int32_t		RpcId;

		std::shared_ptr<IChannel>	__channel;

		const SessionID& SessionId()const;

		const IPEndPoint& Address()const;

		/** @brief 消息到达*/
		void OnRead(const char* data, const size_t len);

		/** @brief 发送消息*/
		void Send(const char* data, const size_t len);

	public:

		void Awake();

		void Destroy();


	private:


	};
}