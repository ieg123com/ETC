#include "model/module/actorlocation/LocationComponent.h"



namespace Hotfix
{
	class LocationComponentAwakeSystem : public AwakeSystem<LocationComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<LocationComponent>& self)override
		{

		}

	};
	REF(LocationComponentAwakeSystem, ObjectSystem);


}