#pragma once
#include "demo/Entity/PlayerEntity.h"

using namespace Model;

namespace Hotfix
{
	class PlayerEntityAwakeSystem : public AwakeSystem<PlayerEntity>
	{
	public:
		virtual void Awake(std::shared_ptr<PlayerEntity> self) override
		{
			LOG_INFO("PlayerEntity Awake");



		}
	};

	REF(PlayerEntityAwakeSystem, ObjectSystem)
}

