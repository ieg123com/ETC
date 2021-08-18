#include "Session.h"
#include "Service.h"
#include "module/message/MessageDefines.h"
#include "etc/etc.h"
#include "IChannel.h"


namespace Model
{

	class SessionAwakeSystem :public AwakeSystem<Session>
	{
	public:
		virtual void Awake(const std::shared_ptr<Session>& self)override
		{
			self->Awake();
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


	const SessionID& Session::SessionId()const
	{
		return (__channel) ? __channel->SessionId : 0;
	}

	const IPEndPoint& Session::Address()const
	{
		static IPEndPoint address_null;
		return (__channel) ? __channel->Address : address_null;
	}

	void Session::Awake()
	{
		RpcId = 0;
	}

	void Session::Destroy()
	{
		if (__channel)
		{
			__channel->Dispose();
			__channel.reset();
		}
	}

	void Session::OnRead(const char* data, const size_t len)
	{



	}

	void Session::Send(const char* data, const size_t len)
	{

	}
}