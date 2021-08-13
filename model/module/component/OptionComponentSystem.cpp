#pragma once
#include "module/component/OptionComponent.h"
#include "other/string/str.h"


using namespace Model;

namespace Hotfix
{

	class OptionComponentAwakeSystem : public AwakeSystem<OptionComponent, int, char* []>
	{
	public:
		virtual void Awake(const std::shared_ptr<OptionComponent>& self, int argc, char* argv[])
		{
			for (int i = 0; i < argc; ++i)
			{
				std::string arg = argv[i];
				size_t pos = arg.find('=');
				if (pos == std::string::npos)continue;
				std::string key = arg.substr(2, pos - 2);
				std::string value = arg.substr(pos + 1, arg.size() - pos - 1);
				LOG_WARN("key {} value {}", key, value);
			}
		}
		 

	};
	REF(OptionComponentAwakeSystem, ObjectSystem);

}


