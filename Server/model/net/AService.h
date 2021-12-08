#pragma once
#include "net/IPEndPoint.h"
#include <functional>
#include <memory>

namespace Model
{
	class ThreadSyncContext;

	class AService :
		public std::enable_shared_from_this<AService>
	{
	public:

		template<typename T>
		std::shared_ptr<T> Get() {
			return std::static_pointer_cast<T>(shared_from_this());
		}

		inline static int64_t CreateChannelId(const int32_t fd) {
			return (INT64_MIN | (int64_t)fd);
		}

		inline static int32_t ChannelIdToSessionId(const int64_t channel_id) {
			return (INT64_MIN ^ (int64_t)channel_id);
		}




		virtual bool IsDisposed() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual bool Create(const int64_t channel_id, const IPEndPoint& address) = 0;
		virtual void Remove(const int64_t channel_id) = 0;
		virtual void Send(const int64_t channel_id, const char* data, const size_t len) = 0;
		virtual void Dispose() = 0;


		std::function<void(const int64_t, const IPEndPoint&)>	AcceptCallback;
		std::function<void(const int64_t, std::shared_ptr<std::vector<char>>)>	ReadCallback;
		std::function<void(const int64_t)>	DisconnectCallback;

		void OnRead(const int64_t channel_id, const std::shared_ptr<std::vector<char>>& data);
		void OnAccept(const int64_t channel_id, const IPEndPoint& address);
		void OnDisconnect(const int64_t channel_id);

	protected:
		ThreadSyncContext* __ThreadSyncContext;

	};
}
