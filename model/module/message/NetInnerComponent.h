#pragma once
#include "net/NetworkComponent.h"

namespace Model
{
	// ÄÚÍø×é¼ş
	class NetInnerComponent :
		public NetworkComponent
	{
	public:


		std::shared_ptr<Session> Get(const IPEndPoint& address);


		std::unordered_map<IPEndPoint, std::shared_ptr<Session>> __m_address_sessions;


	protected:

		virtual void OnDisconnect(const std::shared_ptr<Session>& session) override;

	};
}
