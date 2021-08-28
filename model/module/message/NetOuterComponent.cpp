#include "NetOuterComponent.h"
#include "net/TChannel.h"



namespace Model
{


	void NetOuterComponent::Destroy()
	{
		NetworkComponent::Destroy();
	}


	void NetOuterComponent::OnConnectComplete(const std::shared_ptr<Session>& session)
	{
		session->__channel = ObjectFactory::CreateWithHost<TChannel>(session);
		NetworkComponent::OnConnectComplete(session);
	}

	void NetOuterComponent::OnAccept(const std::shared_ptr<Session>& session)
	{
		session->__channel = ObjectFactory::CreateWithHost<TChannel>(session);
		NetworkComponent::OnAccept(session);
	}

}