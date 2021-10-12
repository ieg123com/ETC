#pragma once
#include "module/message/NetInnerComponent.h"
#include "model/module/message/InnerMessageDispatcher.h"
#include "model/net/tcp/TService.h"
#include "model/net/NetThreadComponent.h"
#include "model/base/thread/ThreadSyncContext.h"

using namespace Model;

namespace Hotfix
{
	class NetInnerComponentAwakeSystem : public AwakeSystem<NetInnerComponent, const IPEndPoint&>
	{
	public:
		virtual void Awake(const std::shared_ptr<NetInnerComponent>& self, const IPEndPoint& addr) override
		{
			self->__MessageDispatcher = new InnerMessageDispatcher();
			auto service = std::make_shared<TService>(ThreadSyncContext::Instance);
			self->__Service = service;
			// 绑定回调函数
			service->AcceptCallback = std::bind(&NetInnerComponent::__OnAccept, self.get(), std::placeholders::_1, std::placeholders::_2);
			service->ReadCallback = std::bind(&NetInnerComponent::__OnRead, self.get(), std::placeholders::_1, std::placeholders::_2);
			service->DisconnectCallback = std::bind(&NetInnerComponent::__OnDisconnect, self.get(), std::placeholders::_1);

			if (!service->Listen(addr))
			{
				throw std::exception(std::format("监听内网端口 %s 失败", addr.ToString().c_str()).c_str());
			}
			NetThreadComponent::Instance->Add(service);
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
			NetThreadComponent::Instance->Remove(self->__Service);
			self->Dispose();
			delete (InnerMessageDispatcher*)self->__MessageDispatcher;
		}
	};
	REF(NetInnerComonentDestroySystem, ObjectSystem);
}
