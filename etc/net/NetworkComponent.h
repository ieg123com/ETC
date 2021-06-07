#pragma once
#include "etc.h"
#include "NetDefines.h"


class Service;
class Session;

// ��������
enum class NetWorkType : uint8_t
{
	Empty,
	Server,
	Clinet,
};


// �������
class NetworkComponent:
	public Component
{
public:

	NetworkComponent() {
		CanEverAwake = true;
	}


	bool Listen(const uint16_t port);

	bool Connect(const std::string& ip, const uint16_t port);

	



	virtual void OnAccept(const std::shared_ptr<Session>& session);

	virtual void OnRead(const std::shared_ptr<Session>& session, const char* data, const size_t len);

	virtual void OnDisconnect(const std::shared_ptr<Session>& session);






protected:

	std::shared_ptr<Service>	m_service;

private:
	// ȫ������
	std::unordered_map<FD, std::shared_ptr<Session>>	m_sessions;
};