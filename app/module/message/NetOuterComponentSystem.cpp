#pragma once
#include "module/message/NetOuterComponent.h"
#include "model/module/message/OuterMessageDispatcher.h"
#include "model/net/NetThreadComponent.h"
#include "model/net/tcp/TService.h"
#include "model/base/thread/ThreadSyncContext.h"
#include "other/string/str.h"
#include <exception>

using namespace Model;

namespace Hotfix
{
	class NetOuterComponentAwakeSystem :public AwakeSystem<NetOuterComponent, const IPEndPoint&>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetOuterComponent>& self, const IPEndPoint& addr) override
		{
			self->__MessageDispatcher = new OuterMessageDispatcher();
			auto service = std::make_shared<TService>(ThreadSyncContext::Instance);
			self->__Service = service;
			// 绑定回调函数
			service->AcceptCallback = std::bind(&NetOuterComponent::__OnAccept, self.get(), std::placeholders::_1, std::placeholders::_2);
			service->ReadCallback = std::bind(&NetOuterComponent::__OnRead, self.get(), std::placeholders::_1, std::placeholders::_2);
			service->DisconnectCallback = std::bind(&NetOuterComponent::__OnDisconnect, self.get(), std::placeholders::_1);

			if (!service->Listen(addr))
			{
				throw std::exception(std::format("监听外网端口 %s 失败", addr.ToString().c_str()).c_str());
			}
			NetThreadComponent::Instance->Add(service);
		}
	};
	REF(NetOuterComponentAwakeSystem, ObjectSystem);



	class NetOuterComponentDestroySystem : public DestroySystem<NetOuterComponent>
	{
	public:
		virtual void Destroy(const std::shared_ptr<NetOuterComponent>& self) override
		{
			NetThreadComponent::Instance->Remove(self->__Service);
			self->Dispose();
			delete (OuterMessageDispatcher*)self->__MessageDispatcher;
		}
	};
	REF(NetOuterComponentDestroySystem, ObjectSystem);
}
