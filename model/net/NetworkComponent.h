#pragma once
#include "etc.h"
#include "Session.h"



class IMessageDispatcher;

namespace Model
{
	class Service;

	// 网络组件
	class NetworkComponent :
		public Component
	{
	public:
		IMessageDispatcher* __MessageDispatcher;



		bool Listen(const IPEndPoint& address);

		std::shared_ptr<Session> Connect(const IPEndPoint& address);


	protected:
		virtual void OnConnectComplete(const std::shared_ptr<Session>& session);

		virtual void OnAccept(const std::shared_ptr<Session>& session);

		virtual void OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len);

		virtual void OnDisconnect(const std::shared_ptr<Session>& session);



		void Destroy();

	private:

		bool __AddSession(const std::shared_ptr<Session>& session);
		bool __RemoveSession(const std::shared_ptr<Session>& session);



	protected:

		std::shared_ptr<Service>	m_sservice;
		//std::shared_ptr<>

		// 全部连接
		std::unordered_map<SessionID, std::shared_ptr<Session>>	m_sessions;
	};
}
