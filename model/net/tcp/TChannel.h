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
	public:
		std::shared_ptr<TService>	__Service;

		AWEpoll* __WEpoll;

		// 接收数据缓冲区
		// 收到数据时，都会添加进RecvBuffer。将在下一帧进行处理
		std::shared_ptr<CircularBuffer>	__RecvBuffer;
		// 发送数据缓冲区
		// 调用Send，会将需要发送的数据添加到SendBuffer。会在LateUpdate中统一发送
		std::shared_ptr<CircularBuffer>	__SendBuffer;

		// 发送的缓存
		// 用于中转SendBuffer中的发送数据
		std::shared_ptr<std::vector<char>>	__SendCache;
		
		PacketParser* __Parser;

		IPEndPoint	RemoteAddress;

		SessionID	SessionId;

		TChannel();
		








		void OnRead(const char* data, const size_t len);

		void Send(const char* data, const size_t len);


		void __StartParse();
		void __StartSend();


	private:


	};
}