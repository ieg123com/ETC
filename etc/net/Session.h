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

	int32_t		RpcId;

	FD			Fd;

	std::string	Ip;

	uint16_t	Port;

	std::shared_ptr<Service>	__service;


	// ��Ϣ����
	void OnRead(const char* data, const size_t len);

	// ������Ϣ
	void Send(const char* data, const size_t len);

protected:

	virtual void Destroy() override;


private:

	//co::Channel<std::function<void()>>	m_channel;



};
