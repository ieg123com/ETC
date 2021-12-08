#include "ActorLocationSenderComponentHandler.h"
#include "model/module/actorlocation/ActorLocationSender.h"

namespace Hotfix
{
	void ActorLocationSenderComponentHandler::Check(const std::shared_ptr<ActorLocationSenderComponent>& self)
	{
		std::vector<ID> timeoutids;

		time_t time_now = Game::Time().NowServerMilliseconds();

		for (auto& item : self->Children)
		{
			auto actor_location_sender = std::static_pointer_cast<ActorLocationSender>(item.second);
			if (time_now > actor_location_sender->LastSendTime + ActorLocationSenderComponent::TIMEOUT_TIME)
			{
				timeoutids.push_back(item.first);
			}
		}

		// 清理过期的请求
		for (ID id : timeoutids)
		{
			self->Remove(id);
		}
	}
}