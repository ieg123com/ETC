#include "etc/etc.h"
#include "model/net/Session.h"

namespace Hotifx
{
	class SessionAwakeSystem :public AwakeSystem<Session, const std::shared_ptr<AService>&>
	{
	public:
		virtual void Awake(const std::shared_ptr<Session>& self, const std::shared_ptr<AService>& service)override
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


}