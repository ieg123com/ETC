#pragma once
#include "module/message/NetInnerComponent.h"

using namespace Model;

namespace Hotfix
{
	class NetInnerComponentAwakeSystem : public AwakeSystem<NetInnerComponent, const IPEndPoint&>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetInnerComponent>& self, const IPEndPoint& addr) override
		{
			if (!self->Listen(addr))
			{
				throw std::exception(std::format("¼àÌýÄÚÍø¶Ë¿Ú %s Ê§°Ü", addr.ToString().c_str()).c_str());
			}
		}
	};
	REF(NetInnerComponentAwakeSystem, ObjectSystem);


}


