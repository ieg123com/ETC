#pragma once
#include <unordered_map>
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


		EpollType		m_type;

		EpollStatus		m_status;
		// 记录已经连接的Socket
		std::unordered_map<SOCKET, stSocketContext*>	m_socket_ctx;

		bool AddSocketCtx(stSocketContext* ctx);
		bool RemoveSocketCtx(const SOCKET fd);
		stSocketContext* GetSocketCtx(const SOCKET fd);

		bool		m_is_disposed;

		const size_t	Backlog = 1000;
		const size_t	MaxEvents = 1024;

	public:
		int			LastError;
		std::string	LastErrorMsg;
		std::string	LastErrorFunction;
		int			LastErrorLine;

		
		bool IsDisposed() const { return m_is_disposed; }


		AWEpoll();


		bool Listen(const IPEndPoint& address);

		bool Connect(const IPEndPoint& address);

		void Close(const SOCKET fd);

		void Dispose();





	private:

		void OnEpollAcceptEvent(stSocketContext* ctx);
		int OnEpollReadableEvent(stSocketContext* ctx);
		int OnEpollWritableEvent(stSocketContext* ctx);
		void OnEpollCloseEvent(stSocketContext* ctx);
		void OnEpollErrorEvent();

	private:



		
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