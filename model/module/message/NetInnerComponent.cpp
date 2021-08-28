#include "NetInnerComponent.h"
#include "net/TChannel.h"



namespace Model
{

	std::shared_ptr<Session> NetInnerComponent::Get(const IPEndPoint& address)
	{
		auto found = __m_address_sessions.find(address);
		if (found != __m_address_sessions.end())
		{
			return found->second;
		}
		if (auto session = Connect(address))
		{
			__m_address_sessions.insert(std::make_pair(address, session));
			return session;
		}
		return nullptr;
	}

	void NetInnerComponent::Destroy()
	{
		NetworkComponent::Destroy();
	}

	void NetInnerComponent::OnConnectComplete(const std::shared_ptr<Session>& session)
	{
		session->__channel = ObjectFactory::CreateWithHost<TChannel>(session);
		NetworkComponent::OnConnectComplete(session);
	}

	void NetInnerComponent::OnAccept(const std::shared_ptr<Session>& session)
	{
		session->__channel = ObjectFactory::CreateWithHost<TChannel>(session);
		NetworkComponent::OnAccept(session);
	}

	void NetInnerComponent::OnDisconnect(const std::shared_ptr<Session>& session)
	{
		NetworkComponent::OnDisconnect(session);
		__m_address_sessions.erase(session->Address);
	}


}