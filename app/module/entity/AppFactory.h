#pragma once
#include "model/module/entity/App.h"
#include "model/module/component/config/StartConfig.h"

using namespace Model;

namespace Hotfix
{
	class AppFactory
	{
	public:


		static std::shared_ptr<App> Create(const std::shared_ptr<GEntity>& host, const std::shared_ptr<StartConfig>& start_config);

	};
}
