#include "Service.h"

namespace Model
{
	void Service::Awake()
	{
		m_closed = false;
	}

	void Service::Destroy()
	{

		OnConnectComplete = nullptr;
		OnAccept = nullptr;
		OnRead = nullptr;
		OnDisconnect = nullptr;
	}

	void Service::WaitClose()
	{
		co::FakeLock lock;
		m_cq.wait(lock, nullptr,
			[&](size_t size)->cond_t::CondRet {
				cond_t::CondRet ret{ true,true };
				if (m_closed)
				{
					ret.canQueue = false;
				}
				return ret;
			});
	}

	void Service::CloseComplete()
	{
		m_closed = true;
		m_cq.notify_all();
	}
}
