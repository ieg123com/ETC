#include "model/net/TChannel.h"


namespace Hotfix
{

	class TChannelAwakeSystem : public AwakeSystem<TChannel>
	{
	public:
		virtual void Awake(const std::shared_ptr<TChannel>& self) override
		{
			self->Awake();
		}
	};
	REF(TChannelAwakeSystem, ObjectSystem);

	class TChannelLateUpdateSystem :public LateUpdateSystem<TChannel>
	{
	public:
		virtual void LateUpdate(const std::shared_ptr<TChannel>& self)override
		{
			self->LateUpdate();
		}
	};
	REF(TChannelLateUpdateSystem, ObjectSystem);

	class TChannelDestroySystem : public DestroySystem<TChannel>
	{
	public:
		virtual void Destroy(const std::shared_ptr<TChannel>& self) override
		{
			self->Destroy();
		}
	};
	REF(TChannelDestroySystem, ObjectSystem);


}