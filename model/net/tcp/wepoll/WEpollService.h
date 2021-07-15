/**
 * @file	WEpollService.h
 * @author	ieg123
 * @create	2021-06-25 5:48 PM
 */
#pragma once
#include "net/Service.h"
//#include "error/error_content.h"

#ifndef _WIN32
#include <sys/epoll.h>
#include <sys/socket.h>
#else
#pragma comment(lib,"ws2_32.lib")
#include "wepoll.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif // !_WIN32


#define WRITE_CONN_ALIVE 0
#define WRITE_CONN_CLOSE 1
#define WRITE_CONN_CONTINUE 2

#define READ_OVER 0
#define READ_CONTINUE 1
#define READ_CLOSE -1

#define READ_BUFFER_SIZE 1024

namespace Model
{
	enum class EpollStatus : uint8_t
	{
		EPOLL_RUNNING = 0,
		EPOLL_STOPPED
	};

	// local server info
	struct stAddressInfo
	{
		IPEndPoint address;
		uint32_t maxEvents;
		uint32_t backlog;
		uint32_t WorkerThreadTaskMax;
		uint32_t timeCheckAcceptClient;

		stAddressInfo()
		{
			maxEvents = 1024;
			backlog = 1000;
			WorkerThreadTaskMax = 0;
			timeCheckAcceptClient = 60;
		}
	};

	// epoll �� ��Ϣ�ַ��� �Ŀͻ�������
	struct stSocketContext
	{
	public:
		std::shared_ptr<Session> session;

		stSocketContext()
		{
		}

		~stSocketContext()
		{

		}
	};

	/** @brief �� wepoll ��װ������������win��linux �·ֱ�ʹ�� iocp��epoll*/
	class WEpollService :
		public Service
	{
	public:
		WEpollService();

		/**
		 * @brief		�򿪲�����ָ���˿�
		 * @param[in]	port : ��Ҫ�����Ķ˿�
		 * @retval		true : �����˿ڳɹ�
		 * @retval		false : �����˿�ʧ��
		 */
		virtual bool Listen(const uint16_t port) override;

		/**
		 * @brief		����ָ��������
		 * @param[in]	ip : Ҫ���ӵķ�������ַ
		 * @param[in]	prot �� �˿�
		 * @retval		Session : ���ӷ������ɹ������ػỰ
		 * @retval		nullptr	: ���ӷ�����ʧ��
		 */
		virtual std::shared_ptr<Session> Connect(const IPEndPoint& address) override;


		virtual void Send(const SessionID fd, const char* data, const size_t len) override;

		virtual void Close(const SessionID fd) override;

	protected:

		virtual void Awake() override;

		virtual void Destroy() override;


	private:

		int OnEpollAcceptEvent(stSocketContext* ctx);
		int OnEpollReadableEvent(stSocketContext* ctx, epoll_event& epoll_event);
		int OnEpollWriteableEvent(stSocketContext* ctx);
		int OnEpollCloseEvent(stSocketContext* ctx);

	private:

		int SetNonBlocking(SessionID fd);

		bool BindOnAddress(const stAddressInfo& addressInfo);

		bool ConnectAddress(const stAddressInfo& addressInfo);


		SessionID AcceptConnectSocket(SessionID sockfd, std::string& client_ip);

		void HandleAcceptEvent(SessionID& epollfd, epoll_event& event);
		void HandleEpollReadableEvent(epoll_event& event);
		void HandleWriteableEvent(SessionID& epollfd, epoll_event& event);
		void DisconnectOneClient(SessionID clientFD);

		bool AddListenSocketToEpoll();
		void HandleEpollEvent(epoll_event& e);
		bool CreateEpoll();

		void StartEpollEventLoop();
		void StartClientEventLoop(std::shared_ptr<Session> session);

		bool StartEpollServer();



		void CloseAndReleaseOneEvent(epoll_event& epoll_event);

	private:

		bool __AddSocketCtx(const SessionID session_id, stSocketContext* ctx);
		bool __RemoveSocketCtx(const SessionID session_id);
		stSocketContext* __GetSocketCtx(const SessionID session_id) const;


	private:

		EpollStatus		m_epoll_status;
		stAddressInfo	m_address_info;
		SessionID		m_listened_socket;

#ifndef _WIN32
		int m_epollfd;
#else
		HANDLE m_epollfd;
#endif

		std::unordered_map<SessionID, stSocketContext*>	m_all_socket_ctx;

	};
}
