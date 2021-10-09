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

		// �������ݻ�����
		// �յ�����ʱ��������ӽ�RecvBuffer��������һ֡���д���
		std::shared_ptr<CircularBuffer>	__RecvBuffer;
		// �������ݻ�����
		// ����Send���Ὣ��Ҫ���͵�������ӵ�SendBuffer������LateUpdate��ͳһ����
		std::shared_ptr<CircularBuffer>	__SendBuffer;

		// ���͵Ļ���
		// ������תSendBuffer�еķ�������
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