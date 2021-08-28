#pragma once
#include "net/NetworkComponent.h"

namespace Model
{
	// ÄÚÍø×é¼þ
	class NetInnerComponent :
		public NetworkComponent
	{
	public:

		std::unordered_map<IPEndPoint, std::shared_ptr<Session>> __m_address_sessions;



		std::shared_ptr<Session> Get(const IPEndPoint& address);


		void Destroy();


	protected:
		virtual void OnConnectComplete(const std::shared_ptr<Session>& session) override;

		virtual void OnAccept(const std::shared_ptr<Session>& session) override;

		virtual void OnDisconnect(const std::shared_ptr<Session>& session) override;

	};
}
