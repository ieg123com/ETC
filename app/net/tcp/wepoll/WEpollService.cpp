#include "model/net/tcp/wepoll/WEpollService.h"



namespace Hotifx
{
	class WEpollServiceAwakeSystem :public AwakeSystem<WEpollService>
	{
	public:
		virtual void Awake(const std::shared_ptr<WEpollService>& self) override
		{
			self->Awake();
		}
	};
	REF(WEpollServiceAwakeSystem, ObjectSystem);

	class WEpollServiceDestroySystem : public DestroySystem<WEpollService>
	{
	public:
		virtual void Destroy(const std::shared_ptr<WEpollService>& self) override
		{
			self->Destroy();
		}
	};
	REF(WEpollServiceDestroySystem, ObjectSystem);
}