#pragma once
#include "etc/etc.h"
#include "AService.h"
#include "thread/ThreadSyncContext.h"


namespace Model
{
	// 网络线程组件
	// 用于更新网络信息
	class NetThreadComponent :
		public Component
	{
	public:
		using ptr = std::shared_ptr<NetThreadComponent>;
		static NetThreadComponent* Instance;

		ThreadSyncContext* ThreadSyncContext;

		std::unordered_set<std::shared_ptr<AService>>	Services;

		

		void Add(const std::shared_ptr<AService>& service)
		{
			auto self = Get<NetThreadComponent>();
			ThreadSyncContext->PostNext([=] {
				if (service->IsDisposed())return;
				self->Services.emplace(service);
				});
		}

		void Remove(const std::shared_ptr<AService>& service)
		{
			auto self = Get<NetThreadComponent>();
			ThreadSyncContext->PostNext([=] {
				if (service->IsDisposed())return;
				self->Services.erase(service);
				});
		}
	};

	
}

