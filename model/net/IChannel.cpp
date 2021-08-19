#include "IChannel.h"
#include "Service.h"

namespace Model
{
	void IChannel::Disconnect()
	{
		if (__service)
		{
			if (__service->GetNetworkType() == NetworkType::Server)
			{
				// 服务类型为服务器
				__service->Close(SessionId);
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

	void IChannel::Awake(const std::shared_ptr<Service>& service)
	{
		__service = service;
	}

}