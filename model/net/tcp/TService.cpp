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

	bool TService::Listen(const IPEndPoint& address)
	{
		return __WEpoll->Listen(address);
	}

	std::shared_ptr<TChannel> TService::GetChannel(const int64_t channel_id)
	{
		auto found = __IdChannels.find(channel_id);
		if (found == __IdChannels.end())
		{
			return nullptr;
		}
		return found->second;
	}

	bool TService::CreateChannel(const int64_t channel_id, const IPEndPoint& address)
	{
		auto found = __IdChannels.find(channel_id);
		if (found != __IdChannels.end())
		{
			return true;
		}
		auto channel = std::make_shared<TChannel>(channel_id, Get<TService>(), address);
		if (!channel->Connect())
		{
			channel->Dispose();
			return false;
		}
		AddChannel(channel);
		return true;
	}

	void TService::Send(const int64_t channel_id, const char* data, const size_t len)
	{
		auto found = __IdChannels.find(channel_id);
		if (found == __IdChannels.end())
		{
			return;
		}
		found->second->Send(data, len);
	}

	void TService::OnComplete(AWEpoll& epoll)
	{
		epoll.OnAccept = std::bind(&TService::OnAcceptComplete, this, std::placeholders::_1, std::placeholders::_2);
		epoll.OnRead = std::bind(&TService::OnReadComplete, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		//epoll.OnWrite = std::bind(&TService::OnWriteComplete, this, std::placeholders::_1, std::placeholders::_2);
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
			LOG_ERROR("接收连接发生错误,fd = {},error = {}",fd,e.what());
		}
		catch (...)
		{
			LOG_ERROR("接收连接发生错误,fd = {},error = 未知错误", fd);
		}
	}

	void TService::OnReadComplete(AWEpoll& epoll, const int32_t fd, const std::shared_ptr<std::vector<char>>& data)
	{
		try
		{
			auto channel = __IdChannels.find(CreateChannelId(fd));
			if (channel == __IdChannels.end())
			{
				// 没找到对应的fd
				return;
			}
			channel->second->OnReadComplete(epoll,fd,data);
		}
		catch (std::exception& e)
		{
			LOG_ERROR("读取数据发生错误,fd = {},error = {}", fd, e.what());
		}
		catch (...)
		{
			LOG_ERROR("读取数据发生错误,fd = {},error = 未知错误", fd);
		}
	}

	void TService::OnDisconnectComplete(AWEpoll& epoll, const int32_t fd)
	{
		try
		{
			auto found = __IdChannels.find(CreateChannelId(fd));
			if (found == __IdChannels.end())
			{
				// 没找到对应的fd
				return;
			}
			found->second->OnDisconnectComplete(epoll,fd);
			auto channel = found->second;
			RemoveChannel(found->second);
			channel->Dispose();
		}
		catch (std::exception& e)
		{
			LOG_ERROR("断开连接发生错误,fd = {},error = {}", fd, e.what());
		}
		catch (...)
		{
			LOG_ERROR("断开连接发生错误,fd = {},error = 未知错误", fd);
		}
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
