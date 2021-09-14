#include "model/module/component/SessionPlayerComponent.h"




namespace Hotfix
{
	class SessionPlayerComponentAwakeSystem :public AwakeSystem<SessionPlayerComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<SessionPlayerComponent>& self)override
		{
			self->ListId = 0;
			self->MapId = 0;
			self->ChatId = 0;
			self->SocialId = 0;
		}
	};
	REF(SessionPlayerComponentAwakeSystem, ObjectSystem);

}