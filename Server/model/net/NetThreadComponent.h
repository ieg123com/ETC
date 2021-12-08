#pragma once
#include "etc/etc.h"
#include "AService.h"
#include "thread/ThreadSyncContext.h"


namespace Model
{
	// �����߳����
	// ���ڸ���������Ϣ
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

