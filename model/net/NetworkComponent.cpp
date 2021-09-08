#include "NetworkComponent.h"
#include "tcp/wepoll/WEpollService.h"
#include "Session.h"
#include "Service.h"
#include "IChannel.h"
#include "log/log.h"


namespace Model
{

	void NetworkComponent::Destroy()
	{
		auto all_sessions = m_sessions;
		for (auto& item : all_sessions)
		{
			item.second->Dispose();
		}

		if (m_sservice)
		{
			m_sservice->Dispose();
		}

	}





	bool NetworkComponent::Listen(const IPEndPoint& address)
	{
		m_sservice = Service::Create<WEpollService>(NetworkType::Server);

		
		m_sservice->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
		m_sservice->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		m_sservice->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

		if (!m_sservice->Listen(address))
		{
			// 开启端口失败
			return false;
		}



		return true;
	}

	std::shared_ptr<Session> NetworkComponent::Connect(const IPEndPoint& address)
	{
		auto service = Service::Create<WEpollService>(NetworkType::Client);

		service->OnConnectComplete = std::bind(&NetworkComponent::OnConnectComplete, this, std::placeholders::_1);
		service->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
		service->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		service->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

		if (auto session = service->Connect(address))
		{
			// 连接成功
			return session;
		}

		// 连接失败
		return nullptr;
	}



	void NetworkComponent::OnConnectComplete(const std::shared_ptr<Session>& session)
	{
		session->__networkcomponent = Get<NetworkComponent>();
		LOG_INFO("完成连接:{} fd:{}", session->Address.ToString(), session->SessionId);
		if (!__AddSession(session))
		{
			LOG_ERROR("连接的会话fd相同");
		}
	}


	void NetworkComponent::OnAccept(const std::shared_ptr<Session>& session)
	{
		session->__networkcomponent = Get<NetworkComponent>();
		LOG_INFO("会话连接:{} fd:{}", session->Address.ToString(), session->SessionId);
		if (!__AddSession(session))
		{
			LOG_ERROR("连接的会话fd相同");
		}
	}

	void NetworkComponent::OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len)
	{
		session->OnRead(data, len);
	}

	void NetworkComponent::OnDisconnect(const std::shared_ptr<Session>& session)
	{
		LOG_INFO("会话断开:{} fd:{}", session->Address.ToString(), session->SessionId);
		if (__RemoveSession(session))
		{
			session->Dispose();
		}
	}

	bool NetworkComponent::__AddSession(const std::shared_ptr<Session>& session)
	{
		return m_sessions.insert(std::make_pair(session->SessionId, session)).second;
	}


	bool NetworkComponent::__RemoveSession(const std::shared_ptr<Session>& session)
	{
		auto found = m_sessions.find(session->SessionId);
		if (found == m_sessions.end())
		{
			return false;
		}
		m_sessions.erase(found);
		return true;
	}
}
