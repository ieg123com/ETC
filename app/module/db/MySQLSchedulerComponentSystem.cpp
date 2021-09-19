#include "model/module/db/MySQLSchedulerComponent.h"





namespace Hotfix
{

	class MySQLSchedulerComponentLoadSystem :public LoadSystem<MySQLSchedulerComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<MySQLSchedulerComponent>& self)override
		{
			MySQLSchedulerComponent::Instance = self.get();
			self->LoadConnectParams();
		}
	};
	REF(MySQLSchedulerComponentLoadSystem, ObjectSystem);
}