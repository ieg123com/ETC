#include "NetThreadComponentHandler.h"


namespace Hotfix
{
	class NetThreadComponentAwakeSystem : public AwakeSystem<NetThreadComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetThreadComponent>& self)override
		{
			self->ThreadSyncContext = ThreadSyncContext::Instance;
		}
	};
	REF(NetThreadComponentAwakeSystem, ObjectSystem);

	class NetThreadComponentLoadSystem :public LoadSystem<NetThreadComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<NetThreadComponent>& self)override
		{
			NetThreadComponent::Instance = self.get();
		}
	};
	REF(NetThreadComponentLoadSystem, ObjectSystem);

	class NetThreadComponentUpdateSystem :public UpdateSystem<NetThreadComponent>
	{
	public:
		virtual void Update(const std::shared_ptr<NetThreadComponent>& self)override
		{
			for (auto& service : self->Services)
			{
				service->Update();
			}
		}
	};
	REF(NetThreadComponentUpdateSystem, ObjectSystem);

	class NetThreadComponentLateUpdateSystem : public LateUpdateSystem<NetThreadComponent>
	{
	public:
		virtual void LateUpdate(const std::shared_ptr<NetThreadComponent>& self)override
		{
			for (auto& service : self->Services)
			{
				service->LateUpdate();
			}
		}
	};
	REF(NetThreadComponentLateUpdateSystem, ObjectSystem);

	class NetThreadComponentDestroySystem :public DestroySystem<NetThreadComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<NetThreadComponent>& self)override
		{
			NetThreadComponent::Instance = nullptr;
			self->ThreadSyncContext = nullptr;
		}
	};
	REF(NetThreadComponentDestroySystem, ObjectSystem);
}