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

		// �������ݻ�����
		// �յ�����ʱ��������ӽ�__RecvBuffer��������һ֡���д���
		// �˱�������__Parser��
		std::shared_ptr<CircularBuffer>	__RecvBuffer;
		// �������ݻ�����
		// ����Send���Ὣ��Ҫ���͵�������ӵ�__SendBuffer������LateUpdate��ͳһ����
		std::shared_ptr<CircularBuffer>	__SendBuffer;

		// ���͵Ļ���
		// ������ת__SendBuffer�еķ�������
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

	private:
		void __StartParse();
		void __StartSend();





	};
}