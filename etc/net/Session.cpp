#include "Session.h"
#include "Service.h"



void Session::Awake()
{
	RpcId = 0;
	Fd = 0;
	Ip = "";
	Port = 0;
}

void Session::Destroy()
{
	if (__service)
	{
		if (__service->GetNetworkType() == NetworkType::Server)
		{
			// 服务类型为服务器
			__service->Close(Fd);
			__service.reset();
		}
		else if (__service->GetNetworkType() == NetworkType::Client)
		{
			// 服务类型为客户端
			__service->Dispose();
			__service.reset();
		}
	}

}

void Session::OnRead(const char* data, const size_t len)
{

}

void Session::Send(const char* data, const size_t len)
{
	__service->Send(Fd, data, len);
}