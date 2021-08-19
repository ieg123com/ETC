#pragma once
#include "NetDefines.h"
#include "etc/etc.h"

namespace Model
{
	class Service;

	class IChannel:
		public GEntity
	{
	public:

		SessionID	SessionId;

		IPEndPoint	Address;

		/** @brief ÍøÂç·þÎñ*/
		std::shared_ptr<Service>	__service;

		virtual void OnRead(const char* data, const size_t len) = 0;

		virtual void Send(const char* data, const size_t len) = 0;

		virtual void Start() = 0;

		virtual void Disconnect();

		void Awake(const std::shared_ptr<Service>& service);


	};
}

