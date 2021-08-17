#pragma once
#include "NetDefines.h"
#include "etc/etc.h"

namespace Model
{
	class Service;

	class IChannel
	{
	public:

		SessionID	SessionId;

		IPEndPoint	Address;

		/** @brief ÍøÂç·þÎñ*/
		std::shared_ptr<Service>	__service;

		IChannel(std::shared_ptr<Service> serv) {
			__service = serv;
		}


		virtual void OnRead(const char* data, const size_t len) = 0;

		virtual void Send(const char* data, const size_t len) = 0;

		virtual void Start() = 0;

		virtual void Disconnect();

	};
}

