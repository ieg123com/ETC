#pragma once
#include "NetDefines.h"
#include "etc/etc.h"

namespace Model
{
	class Service;
	class Session;

	class IChannel:
		public GEntity
	{
	public:

		std::shared_ptr<Session>	__session;

		virtual void OnRead(const char* data, const size_t len) = 0;

		virtual void Send(const char* data, const size_t len) = 0;

		virtual void Start() = 0;


		void Awake();

		void Destroy();

	};
}

