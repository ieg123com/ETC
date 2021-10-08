#include "NetThreadComponentHandler.h"


namespace Hotfix
{
	class NetThreadComponentAwakeSystem : public AwakeSystem<NetThreadComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetThreadComponent>& self)override
		{

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

	class NetThreadComponentLateUpdateSystem : public LateUpdateSystem<NetThreadComponent>
	{
	public:
		virtual void LateUpdate(const std::shared_ptr<NetThreadComponent>& self)override
		{

		}
	};
	REF(NetThreadComponentLateUpdateSystem, ObjectSystem);

	class NetThreadComponentDestroySystem :public DestroySystem<NetThreadComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<NetThreadComponent>& self)override
		{
			NetThreadComponent::Instance = nullptr;
		}
	};
	REF(NetThreadComponentDestroySystem, ObjectSystem);
}