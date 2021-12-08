#pragma once
#include "demo/Entity/UnitEntity.h"


using namespace Model;

namespace Hotfix
{

	class UnitEntityAwakeSystem : public AwakeSystem<UnitEntity>
	{
	public:
		virtual void Awake(const std::shared_ptr<UnitEntity>& self) override
		{
			
		}
	};
	REF(UnitEntityAwakeSystem,ObjectSystem)

}

