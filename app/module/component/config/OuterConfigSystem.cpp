#include "module/component/config/OuterConfig.h"
#include "other/json/cJsonHelper.h"


using namespace Model;

namespace Hotfix
{
	class OuterConfigAwakeSystem :public AwakeSystem<OuterConfig,cJSON*>
	{
	public:
		virtual void Awake(const std::shared_ptr<OuterConfig>& self,cJSON* json) override
		{
			std::string addr;
			if (!cJSON_Get(json, "Address", addr))
			{
				throw std::exception("OuterConfig ���ü���ʧ��!(û�ҵ� Address ����)");
			}
			self->Address = addr;
		}
	};
	REF(OuterConfigAwakeSystem, ObjectSystem);
}
