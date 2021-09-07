#pragma once
#include "module/message/NetInnerComponent.h"
#include "model/module/message/InnerMessageDispatcher.h"

using namespace Model;

namespace Hotfix
{
	class NetInnerComponentAwakeSystem : public AwakeSystem<NetInnerComponent, const IPEndPoint&>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetInnerComponent>& self, const IPEndPoint& addr) override
		{
			self->__MessageDispatcher = new InnerMessageDispatcher();
			if (!self->Listen(addr))
			{
				throw std::exception(std::format("¼àÌýÄÚÍø¶Ë¿Ú %s Ê§°Ü", addr.ToString().c_str()).c_str());
			}
		}
	};
	REF(NetInnerComponentAwakeSystem, ObjectSystem);

	class NetInnerComponentLoadSystem : public LoadSystem<NetInnerComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<NetInnerComponent>& self)override
		{
			NetInnerComponent::Instance = self.get();
		}
	};
	REF(NetInnerComponentLoadSystem, ObjectSystem);

	class NetInnerComonentDestroySystem : public DestroySystem<NetInnerComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<NetInnerComponent>& self)override
		{
			self->Dispose();
			delete (InnerMessageDispatcher*)self->__MessageDispatcher;
		}
	};
	REF(NetInnerComonentDestroySystem, ObjectSystem);
}


