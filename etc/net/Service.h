#pragma once
#include "etc.h"
#include "NetDefines.h"




class Service:
	public GEntity
{
	friend class Session;
	friend class NetworkComponent;
public:

	virtual bool Listen(const uint16_t port) { return false; }

	virtual std::shared_ptr<Session> Connect(const std::string& ip, const uint16_t port){ return false; }



	virtual void Send(const FD fd, const char* data, const size_t len){}


protected:

	// »Øµ÷
	std::function<void(std::shared_ptr<Session>&)>					OnConnectComplete;
	std::function<void(std::shared_ptr<Session>&)>					OnAccept;
	std::function<void(std::shared_ptr<Session>&, char*, size_t)>	OnRead;
	std::function<void(std::shared_ptr<Session>&)>					OnDisconnect;


};