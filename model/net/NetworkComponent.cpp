#include "NetworkComponent.h"
#include "tcp/wepoll/WEpollService.h"
#include "Session.h"
#include "log/log.h"


namespace Model
{
	bool NetworkComponent::Listen(const IPEndPoint& address)
	{
		m_service = Service::Create<WEpollService>(NetworkType::Server);


		m_service->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
		m_service->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		m_service->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

		if (!m_service->Listen(address))
		{
			// 开启端口失败
			return false;
		}



		return true;
	}

	std::shared_ptr<Session> NetworkComponent::Connect(const IPEndPoint& address)
	{
		m_service = Service::Create<WEpollService>(NetworkType::Client);

		m_service->OnConnectComplete = std::bind(&NetworkComponent::OnConnectComplete, this, std::placeholders::_1);
		m_service->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
		m_service->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		m_service->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

		if (auto session = m_service->Connect(address))
		{
			// 连接成功
			return session;
		}

		// 连接失败
		return nullptr;
	}



	void NetworkComponent::OnConnectComplete(const std::shared_ptr<Session>& session)
	{
		LOG_INFO("完成连接:{} fd:{}", session->Address.ToString(), session->SessionId);
		if (!__AddSession(session))
		{
			LOG_ERROR("连接的会话fd相同");
		}
	}


	void NetworkComponent::OnAccept(const std::shared_ptr<Session>& session)
	{
		LOG_INFO("会话连接:{} fd:{}", session->Address.ToString(), session->SessionId);

		if (!__AddSession(session))
		{
			LOG_ERROR("连接的会话fd相同");
		}
		else {
			session->Send("Welcome ETC", 11);
		}

	}

	void NetworkComponent::OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len)
	{
		LOG_INFO("Ip:{} fd:{}\n{}",
			session->Address.ToString(),
			session->SessionId,
			data);
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
