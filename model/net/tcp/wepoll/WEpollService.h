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

	// epoll 到 消息分发层 的客户端数据
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

	/** @brief 用 wepoll 封装的网络服务对象，win、linux 下分别使用 iocp、epoll*/
	class WEpollService :
		public Service
	{
	public:
		WEpollService();

		/**
		 * @brief		打开并监听指定端口
		 * @param[in]	port : 需要监听的端口
		 * @retval		true : 监听端口成功
		 * @retval		false : 开启端口失败
		 */
		virtual bool Listen(const uint16_t port) override;

		/**
		 * @brief		连接指定服务器
		 * @param[in]	ip : 要连接的服务器地址
		 * @param[in]	prot ： 端口
		 * @retval		Session : 连接服务器成功，返回会话
		 * @retval		nullptr	: 连接服务器失败
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
