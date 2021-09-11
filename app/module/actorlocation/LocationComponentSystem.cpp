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


	class LocationComponentLoadSystem : public LoadSystem<LocationComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<LocationComponent>& self)override
		{

		}

	};
	REF(LocationComponentLoadSystem, ObjectSystem);
}