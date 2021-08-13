#include "OuterConfig.h"



namespace Model
{
	class OuterConfigAwakeSystem :public AwakeSystem<OuterConfig>
	{
	public:
		virtual void Awake(const std::shared_ptr<OuterConfig>& self) override
		{
			
		}
	};

}
