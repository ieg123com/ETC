#include "TService.h"
#include "TChannel.h"
#include "wepoll/AWEpoll.h"
#include "thread/ThreadSyncContext.h"
#include "log/log.h"


namespace Model
{
	TService::TService(ThreadSyncContext* thread_sync)
	{
		__ThreadSyncContext = thread_sync;
		__WEpoll = std::make_shared<AWEpoll>();
		__WEpoll->OnComplete = std::bind(&TService::OnComplete, this, std::placeholders::_1);
	}

	void TService::OnComplete(AWEpoll& epoll)
	{
		epoll.OnAccept = std::bind(&TService::OnAcceptComplete, this, std::placeholders::_1, std::placeholders::_2);
		epoll.OnRead = std::bind(&TService::OnReadComplete, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		epoll.OnWrite = std::bind(&TService::OnWriteComplete, this, std::placeholders::_1, std::placeholders::_2);
		epoll.OnDisconnect = std::bind(&TService::OnDisconnectComplete, this, std::placeholders::_1, std::placeholders::_2);
	}

	void TService::OnAcceptComplete(AWEpoll& epoll, const int32_t fd)
	{
		try {
			int64_t channel_id = CreateChannelId(fd);
			auto channel = std::make_shared<TChannel>(channel_id, Get<TService>(), __WEpoll);
			channel->SessionId = fd;
			channel->RemoteAddress = epoll.GetIPEndPointTry(fd);
			AddChannel(channel);

			OnAccept(channel_id, channel->RemoteAddress);
		}
		catch (std::exception& e)
		{
			LOG_ERROR("测试   ");
		}

	}

	void TService::OnReadComplete(AWEpoll& epoll, const int32_t fd, const std::shared_ptr<std::vector<char>>& data)
	{

	}

	void TService::OnWriteComplete(AWEpoll& epoll, const int32_t fd)
	{

	}

	void TService::OnDisconnectComplete(AWEpoll& epoll, const int32_t fd)
	{

	}


	void TService::AddChannel(const std::shared_ptr<TChannel>& channel)
	{
		if (__IdChannels.emplace(channel->Id, channel).second == false)
		{
			return;
		}
		if (channel->ChannelType == EChannelType::Connect)
		{
			auto self = Get<TService>();
			__ThreadSyncContext->PostNext([=] {
				self->__UpdateChannels.emplace(channel->Id, channel);
				});
		}

	}

	void TService::RemoveChannel(const std::shared_ptr<TChannel>& channel)
	{
		if (channel->ChannelType == EChannelType::Connect)
		{
			auto self = Get<TService>();
			__ThreadSyncContext->PostNext([=] {
				self->__UpdateChannels.erase(channel->Id);
				});
		}
		__IdChannels.erase(channel->Id);
	}
}
