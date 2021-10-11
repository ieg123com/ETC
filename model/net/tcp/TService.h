#pragma once
#include "net/AService.h"
#include <unordered_set>
#include <unordered_map>


namespace Model
{
	class AWEpoll;
	class TChannel;


	class TService :
		public AService
	{
		std::unordered_map<int64_t, std::shared_ptr<TChannel>>	__IdChannels;
		// 需要更新的 Channel
		std::unordered_map<int64_t, std::shared_ptr<TChannel>>	__UpdateChannels;
	public:
		
		// 需要发送的channel id
		std::unordered_set<int64_t>		__NeedStartSend;

		std::shared_ptr<AWEpoll> __WEpoll;

		TService(ThreadSyncContext* thread_sync);

		bool Listen(const IPEndPoint& address);
			

		std::shared_ptr<TChannel> GetChannel(const int64_t channel_id);
		bool CreateChannel(const int64_t channel_id, const IPEndPoint& address);
		
		void Send(const int64_t channel_id, const char* data, const size_t len);
	private:
		void OnComplete(AWEpoll& epoll);
		void OnAcceptComplete(AWEpoll& epoll, const int32_t fd);
		void OnReadComplete(AWEpoll& epoll, const int32_t fd, const std::shared_ptr<std::vector<char>>& data);
		void OnDisconnectComplete(AWEpoll& epoll, const int32_t fd);





		void AddChannel(const std::shared_ptr<TChannel>& channel);
		void RemoveChannel(const std::shared_ptr<TChannel>& channel);


	};
}