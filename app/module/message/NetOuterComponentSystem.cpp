#pragma once
#include "module/message/NetOuterComponent.h"
#include "model/module/message/OuterMessageDispatcher.h"
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
			self->__MessageDispatcher = new OuterMessageDispatcher();
			if (!self->Listen(addr))
			{
				throw std::exception(std::format("¼àÌýÍâÍø¶Ë¿Ú %s Ê§°Ü", addr.ToString().c_str()).c_str());
			}

		}
	};
	REF(NetOuterComponentAwakeSystem, ObjectSystem);

	class NetOuterComponentDestroySystem : public DestroySystem<NetOuterComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<NetOuterComponent>& self) override
		{
			self->Dispose();
			delete (OuterMessageDispatcher*)self->__MessageDispatcher;
		}
	};
	REF(NetOuterComponentDestroySystem, ObjectSystem);
}

