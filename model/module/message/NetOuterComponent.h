#pragma once
#include "net/NetworkComponent.h"


namespace Model
{
	// ÍâÍø×é¼þ
	class NetOuterComponent :
		public NetworkComponent
	{
	public:
		static NetOuterComponent* Instance;

		void Destroy();


	protected:
		virtual void OnConnectComplete(const std::shared_ptr<Session>& session) override;

		virtual void OnAccept(const std::shared_ptr<Session>& session) override;
	};
}
