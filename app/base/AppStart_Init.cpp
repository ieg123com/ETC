#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"

namespace Hotfix
{
	class AppStart_Init :public EventSystem<SystemEvent::AppStart&>
	{
	public:
		virtual void Run(SystemEvent::AppStart& app_start)override
		{
			LOG_INFO("AppStart_Init");
		}
	};
	REF(AppStart_Init, Event);


}