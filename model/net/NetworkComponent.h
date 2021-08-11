#pragma once
#include "etc.h"
#include "Session.h"




namespace Model
{
	// 网络组件
	class NetworkComponent :
		public Component
	{
	public:


		bool Listen(const uint16_t port);

		std::shared_ptr<Session> Connect(const IPEndPoint& address);



		virtual void OnConnectComplete(const std::shared_ptr<Session>& session);

		virtual void OnAccept(const std::shared_ptr<Session>& session);

		virtual void OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len);

		virtual void OnDisconnect(const std::shared_ptr<Session>& session);


	private:

		bool __AddSession(const std::shared_ptr<Session>& session);
		bool __RemoveSession(const std::shared_ptr<Session>& session);



	protected:

		std::shared_ptr<Service>	m_service;

	private:
		// 全部连接
		std::unordered_map<SessionID, std::shared_ptr<Session>>	m_sessions;
	};
}
