#pragma once
#include "module/message/NetOuterComponent.h"
#include "other/string/str.h"
#include <exception>

using namespace Model;

namespace Hotfix
{
	class NetOuterComponentAwakeSystem :public AwakeSystem<NetOuterComponent,const IPEndPoint&>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetOuterComponent>& self, const IPEndPoint& addr) override
		{
			if (!self->Listen(addr))
			{
				throw std::exception(std::format("¼àÌýÍâÍø¶Ë¿Ú %s Ê§°Ü", addr.ToString().c_str()).c_str());
			}

		}
	};
	REF(NetOuterComponentAwakeSystem, ObjectSystem);



}

