#pragma once
#include "net/AChannel.h"
#include "net/NetDefines.h"
#include "other/container/CircularBuffer.h"


namespace Model
{
	class AWEpoll;
	class TService;
	class PacketParser;

	class TChannel :
		public AChannel
	{
		std::shared_ptr<TService>	__Service;

		std::shared_ptr<AWEpoll> __WEpoll;

		// 接收数据缓冲区
		// 收到数据时，都会添加进__RecvBuffer。将在下一帧进行处理
		// 此变量会与__Parser绑定
		std::shared_ptr<CircularBuffer>	__RecvBuffer;
		// 发送数据缓冲区
		// 调用Send，会将需要发送的数据添加到__SendBuffer。会在LateUpdate中统一发送
		std::shared_ptr<CircularBuffer>	__SendBuffer;

		// 发送的缓存
		// 用于中转__SendBuffer中的发送数据
		std::shared_ptr<std::vector<char>>	__SendCache;

		PacketParser* __Parser;

		bool	__IsSending;
		bool	__IsConnected;

	public:
		SessionID	SessionId;

		TChannel(const int64_t id, const std::shared_ptr<TService>& service, const std::shared_ptr<AWEpoll>& epoll);
		TChannel(const int64_t id, const std::shared_ptr<TService>& service, const IPEndPoint& address);


		virtual bool IsDisposed() const override;

		virtual void Dispose() override;


		bool Connect();







		void Send(const char* data, const size_t len);



		void OnComplete(AWEpoll& epoll);
		void OnConnectComplete(AWEpoll& epoll, const int32_t fd);
		void OnReadComplete(AWEpoll& epoll, const int32_t fd, const std::shared_ptr<std::vector<char>>& data);
		void OnDisconnectComplete(AWEpoll& epoll, const int32_t fd);


		void __StartRecv();
		void __StartParse();
		void __StartSend();





	};
}
