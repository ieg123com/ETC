#include "NetworkComponent.h"
#include "tcp/wepoll/WEpollService.h"
#include "Session.h"
#include "log/log.h"


bool NetworkComponent::Listen(const uint16_t port)
{
	m_service = ObjectFactory::Create<WEpollService>();


	m_service->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
	m_service->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	m_service->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

	if (!m_service->Listen(port))
	{
		// 开启端口失败
		return false;
	}



	return true;
}

bool NetworkComponent::Connect(const std::string& ip, const uint16_t port)
{
	m_service = ObjectFactory::Create<WEpollService>();

	m_service->OnAccept = std::bind(&NetworkComponent::OnAccept, this, std::placeholders::_1);
	m_service->OnRead = std::bind(&NetworkComponent::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	m_service->OnDisconnect = std::bind(&NetworkComponent::OnDisconnect, this, std::placeholders::_1);

	if (!m_service->Connect(ip,port))
	{
		// 开启端口失败
		return false;
	}

	return true;
}





void NetworkComponent::OnAccept(const std::shared_ptr<Session>& session)
{
	LOG_INFO("会话连接:{} fd:{}", session->Ip.c_str(),session->Fd);

	if (m_sessions.insert(std::make_pair(session->Fd, session)).second == false)
	{
		LOG_ERROR("连接的会话fd相同");
	}
}

void NetworkComponent::OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len)
{
	LOG_INFO("Ip:{} fd:{}\n{}",
		session->Ip.c_str(),
		session->Fd,
		data);
	session->OnRead(data, len);
}

void NetworkComponent::OnDisconnect(const std::shared_ptr<Session>& session)
{
	LOG_INFO("会话断开:{} fd:{}", session->Ip.c_str(), session->Fd);
	m_sessions.erase(session->Fd);
	session->Dispose();
}