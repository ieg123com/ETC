#pragma once
#include <unordered_map>
#include <functional>
#include "net/IPEndPoint.h"

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

	class AWEpoll
	{
		// 类型
		enum class EpollType : uint8_t
		{
			Server,	// 服务
			Connect	// 连接
		};

		enum class EpollStatus : uint8_t
		{
			RUNNING,
			STOPPED
		};

		// 套接字信息
		struct stSocketContext
		{
			SOCKET	fd;
			IPEndPoint	Address;
		};

		const size_t	Backlog = 1000;
		const size_t	MaxEvents = 1024;

		EpollType		m_type;

		EpollStatus		m_status;
		// 记录已经连接的Socket
		std::unordered_map<SOCKET, stSocketContext*>	m_socket_ctx;

		bool AddSocketCtx(stSocketContext* ctx);
		bool RemoveSocketCtx(const SOCKET fd);
		stSocketContext* GetSocketCtx(const SOCKET fd);

		bool		m_is_disposed;


		// 事件缓存
		epoll_event*	m_events;


	public:
		int			LastError;
		std::string	LastErrorMsg;
		std::string	LastErrorFunction;
		int			LastErrorLine;

		// 回调
		std::function<void(AWEpoll&, int)>			OnConnectComplete;
		std::function<void(AWEpoll&, int)>			OnAccept;
		std::function<void(AWEpoll&, int,const std::shared_ptr<std::string>&)>			OnRead;
		std::function<void(AWEpoll&, int)>			OnWrite;
		std::function<void(AWEpoll&, int)>			OnDisconnect;

		
		bool IsDisposed() const { return m_is_disposed; }

		IPEndPoint GetIPEndPointTry(const int fd)const;


		AWEpoll();


		bool Listen(const IPEndPoint& address);

		bool Connect(const IPEndPoint& address);

		void Disconnect(const SOCKET fd);

		void Dispose();

		bool Send(const int fd, const char* data, const size_t len);
		bool Send(const char* data, const size_t len);


		void Update();


	private:

		void OnEpollConnectComplete();
		void OnEpollAcceptEvent(stSocketContext* ctx);
		int OnEpollReadableEvent(stSocketContext* ctx);
		int OnEpollReadableEvent(int fd);
		int OnEpollWritableEvent(stSocketContext* ctx);
		int OnEpollWritableEvent(int fd);
		void OnEpollCloseEvent(stSocketContext* ctx);
		void OnEpollErrorEvent();

	private:

		void __Dispose();
		void __Disconnect(const int fd);

		
		// 处理连接事件
		void HandleAcceptEvent(const int epoll_fd, epoll_event& event);
		// 处理读取事件
		void HandleEpollReadableEvent(epoll_event& event);
		// 处理写入事件
		void HandleWritableEvent(const int epoll_fd, epoll_event& event);
		// 处理断开事件
		void HandleCloseEvent(epoll_event& event);


		// 绑定地址
		bool BindOnAddress(const IPEndPoint& address);
		// 连接地址
		bool ConnectAddress(const IPEndPoint& address);


		bool CreateEpoll();
		bool AddListenSocketToEpoll();
		// 处理epoll事件
		void HandleEpollEvent(epoll_event& event);
		// 接受连接的会话
		SOCKET AcceptConnectSocket(const SOCKET fd, IPEndPoint& address);



		SOCKET	m_socket;

#ifndef _WIN32
		int	m_epoll_fd;
#else
		HANDLE	m_epoll_fd;
#endif

	};


}