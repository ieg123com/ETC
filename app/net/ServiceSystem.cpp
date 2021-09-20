#include "model/net/Service.h"



namespace Hotifx
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

}