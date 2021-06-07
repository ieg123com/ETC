#pragma once
#include "etc.h"
#include "coroutine.h"
#include "NetDefines.h"
#include <string>


class Service;


class Session :
	public GEntity
{
	friend class Service;
public:

	static std::shared_ptr<Session> Create(std::shared_ptr<Service> ser, FD fd, const std::string& ip);;


	int32_t		RpcId;

	FD			Fd;

	std::string	Ip;

	std::shared_ptr<Service>	__service;


	// 消息到达
	/*void OnRead(const char* data, const size_t len);*/

	// 发送消息
	void Send(const char* data, const size_t len);

protected:

	virtual void Destroy() override;


private:

	co::Channel<std::function<void()>>	m_channel;



};
