#pragma once
#include "net/AChannel.h"
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

		std::shared_ptr<CircularBuffer>	__RecvBuffer;
		std::shared_ptr<CircularBuffer>	__SendBuffer;

		PacketParser* __Parser;

		TChannel();
		








		void OnRead(const char* data, const size_t len);

		void Send(const char* data, const size_t len);


		void __StartParse();
		void __StartSend();


	private:


	};
}