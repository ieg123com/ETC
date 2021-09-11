#include "model/module/actorlocation/LocationProxyComponent.h"



namespace Hotfix
{
	class LocationProxyComponentAwakeSystem :public AwakeSystem<LocationProxyComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<LocationProxyComponent>& self)override
		{

		}
	};
	REF(LocationProxyComponentAwakeSystem, ObjectSystem);

	class LocationProxyComponentLoadSystem :public LoadSystem<LocationProxyComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<LocationProxyComponent>& self)override
		{

		}
	};
	REF(LocationProxyComponentLoadSystem, ObjectSystem);
}