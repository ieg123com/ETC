#include "AppFactory.h"
#include "etc/etc.h"
#include "model/module/message/NetOuterComponent.h"
#include "model/module/actorlocation/LocationComponent.h"
#include "model/module/actor/MailBoxComponent.h"

namespace Hotfix
{
	std::shared_ptr<App> AppFactory::Create(const std::shared_ptr<GEntity>& host, const std::shared_ptr<StartConfig>& start_config)
	{
		auto app = ObjectFactory::CreateWithHostAndInstanceId<App>(host, start_config->InstanceId);
		app->Id = start_config->AppId;
		app->AddComponent<MailBoxComponent, MailBoxType>(MailBoxType::UnorderedMessageDispatcher);
		switch (start_config->AppType)
		{
		case EAppType::Gate:
			app->AddComponent<NetOuterComponent, const IPEndPoint&>(start_config->OuterAddress);
			break;
		case EAppType::Login:
			app->AddComponent<NetOuterComponent, const IPEndPoint&>(start_config->OuterAddress);
			break;
		case EAppType::List:
			break;
		case EAppType::Map:
			break;
		case EAppType::Location:
			app->AddComponent<LocationComponent>();
			break;
		case EAppType::Chat:
			break;
		case EAppType::Social:
			break;
		default:
			break;
		}
		return app;
	}
}