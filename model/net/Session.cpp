#include "Session.h"
#include "Service.h"
#include "module/message/MessageDefines.h"
#include "etc/etc.h"
#include "IChannel.h"


namespace Model
{

	class SessionAwakeSystem :public AwakeSystem<Session,const std::shared_ptr<Service>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<Session>& self, const std::shared_ptr<Service>& service)override
		{
			self->Awake(service);
		}
	};
	REF(SessionAwakeSystem, ObjectSystem);

	class SessionDestroySystem :public DestroySystem<Session>
	{
	public:
		virtual void Destroy(const std::shared_ptr<Session>& self) override
		{
			self->Destroy();
		}
	};
	REF(SessionDestroySystem, ObjectSystem);


	void Session::Awake(const std::shared_ptr<Service>& service)
	{
		RpcId = 0;
		__service = service;
	}

	void Session::Destroy()
	{
		// Service
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
		// IChannel
		if (__channel)
		{
			__channel->Dispose();
			__channel.reset();
		}
	}

	void Session::OnRead(const char* data, const size_t len)
	{
		if (__channel)
		{
			__channel->OnRead(data, len);
		}
	}

	void Session::Send(const char* data, const size_t len)
	{
		if (__channel)
		{
			__channel->Send(data, len);
		}
	}
}