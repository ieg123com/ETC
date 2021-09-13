#pragma once
#include "model/module/actorlocation/ActorLocationSenderComponent.h"


namespace Hotfix
{
	class ActorLocationSenderComponentHandler
	{
	public:
		static void Check(const std::shared_ptr<ActorLocationSenderComponent>& self);
	};

}