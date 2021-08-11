#include "Service.h"
#include "etc/etc.h"

namespace Model
{

	class ServiceAwakeSystem :public AwakeSystem<Service>
	{
	public:
		virtual void Awake(const std::shared_ptr<Service>& self) override
		{
			self->Awake();
		}
	};
	REF(ServiceAwakeSystem, ObjectSystem);

	class ServiceDestroySystem :public DestroySystem<Service>
	{
	public:
		virtual void Destroy(const std::shared_ptr<Service>& self) override
		{
			self->Destroy();
		}
	};
	REF(ServiceDestroySystem, ObjectSystem);


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
