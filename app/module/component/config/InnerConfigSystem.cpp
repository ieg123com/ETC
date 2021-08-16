#include "module/component/config/InnerConfig.h"
#include "other/json/cJsonHelper.h"

namespace Model
{
	class InnerConfigAwakeSystem :public AwakeSystem<InnerConfig, cJSON*>
	{
	public:
		virtual void Awake(const std::shared_ptr<InnerConfig>& self, cJSON* json) override
		{
			std::string addr;
			if (!cJSON_Get(json, "Address", addr))
			{
				throw std::exception("InnerConfig ���ü���ʧ��!(û�ҵ� Address ����)");
			}
			self->Address = addr;
		}
	};
	REF(InnerConfigAwakeSystem, ObjectSystem);
}