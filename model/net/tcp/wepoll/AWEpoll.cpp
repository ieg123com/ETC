#include "AWEpoll.h"
#ifndef _WIN32
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#else
#endif // !_WIN32
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cerrno>
#include <errno.h>
#include <string.h>
#include "string/str.h"


#define AWEPOLL_ERROR(err_code,err_msg) \
{\
	LastError = err_code;\
	LastErrorMsg = err_msg;\
	LastErrorFunction = __FUNCTION__;\
	LastErrorLine = __LINE__;\
}

namespace Model
{


	int SetNonBlocking(SOCKET s)
	{
#ifndef _WIN32
		int flags;
		if (-1 == (flags = fcntl(s, F_GETFL, 0)))
			flags = 0;
		return fcntl(s, F_SETFL, flags | O_NONBLOCK);
#else
		unsigned long flags = 1; /* 这里根据需要设置成0或1 */
		return ioctlsocket(s, FIONBIO, &flags);
#endif
	};


	bool AWEpoll::AddSocketCtx(AWEpoll::stSocketContext* ctx)
	{
		return m_socket_ctx.emplace(ctx->fd, ctx->Address).second;
	}

	bool AWEpoll::RemoveSocketCtx(const SOCKET fd)
	{
		auto found = m_socket_ctx.find(fd);
		if (found == m_socket_ctx.end())
		{
			return false;
		}
		m_socket_ctx.erase(fd);
		return true;
	}

	AWEpoll::stSocketContext* AWEpoll::GetSocketCtx(const SOCKET fd)
	{
		auto found = m_socket_ctx.find(fd);
		if (found == m_socket_ctx.end())
		{
			return nullptr;
		}
		return found->second;
	}

	AWEpoll::AWEpoll()
	{
		m_type = EpollType::Server;
		m_status = EpollStatus::STOPPED;
		m_socket = SOCKET_ERROR;
		m_epoll_fd = nullptr;
		m_is_disposed = false;

	}

	bool AWEpoll::Listen(const IPEndPoint& address)
	{

	}

	bool AWEpoll::Connect(const IPEndPoint& address)
	{

	}

	void AWEpoll::Close(const SOCKET fd)
	{

	}

	void AWEpoll::Dispose()
	{
		m_is_disposed = true;
	}






	void AWEpoll::HandleAcceptEvent(const int epoll_fd, epoll_event& event)
	{
		int sockfd = event.data.fd;

		IPEndPoint address;
		SOCKET conn_sock = AcceptConnectSocket(sockfd, address);
		if (conn_sock == SOCKET_ERROR)
		{
			OnEpollErrorEvent();
			return;
		}
		if (0 != SetNonBlocking(conn_sock))
		{
			AWEPOLL_ERROR(SOCKET_ERROR, "set conn sock nonblocking failed!");
			OnEpollErrorEvent();
			return;
		}


		// 创建新会话
		stSocketContext* ctx = new stSocketContext();
		ctx->fd = conn_sock;
		ctx->Address = std::move(address);

		if (!AddSocketCtx(ctx))
		{
			AWEPOLL_ERROR(SOCKET_ERROR, "abnormal fd allocation!");
			OnEpollErrorEvent();
			return;
		}

		OnEpollAcceptEvent(ctx);

		struct epoll_event conn_sock_ev;
#ifdef _WIN32
		conn_sock_ev.events = EPOLLIN | EPOLLONESHOT;
#else
		conn_sock_ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
#endif
		conn_sock_ev.data.ptr = ctx;

		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, conn_sock, &conn_sock_ev) == -1)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			HandleCloseEvent(event);
			OnEpollErrorEvent();
			return;
		}
	}

	void AWEpoll::HandleEpollReadableEvent(epoll_event& event)
	{
		auto ctx = (stSocketContext*)event.data.ptr;
		int fd = ctx->fd;


		int ret = OnEpollReadableEvent(ctx);

		if (ret == READ_CLOSE)
		{
			HandleCloseEvent(event);
			return;
		}
		if (ret == READ_CONTINUE)
		{
			event.events = EPOLLIN | EPOLLONESHOT;
			epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &event);
		}
		else if (ret == READ_OVER)
		{ // READ_OVER
			event.events = EPOLLOUT | EPOLLONESHOT;
			epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &event);
		}
		else
		{
			AWEPOLL_ERROR(SOCKET_ERROR, std::format("Unknown read ret: %d", ret));
			//OnEpollErrorEvent();
			return;
		}
	}

	void AWEpoll::HandleWritableEvent(const int epoll_fd, epoll_event& event)
	{
		auto ctx = (stSocketContext*)event.data.ptr;
		int fd = ctx->fd;

		int ret = OnEpollWritableEvent(ctx);
		if (ret == WRITE_CONN_CLOSE)
		{
			HandleCloseEvent(event);
			return;
		}

		if (ret == WRITE_CONN_CONTINUE)
		{
			event.events = EPOLLOUT | EPOLLONESHOT;
		}
		else if (ret == WRITE_CONN_ALIVE)
		{
			// wait for next request
			event.events = EPOLLIN | EPOLLONESHOT;
		}
		else
		{
			AWEPOLL_ERROR(SOCKET_ERROR, std::format("Unknown write ret: %d", ret));
		}
#ifndef _WIN32
		epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event);
#else
		epoll_ctl((HANDLE)epoll_fd, EPOLL_CTL_MOD, fd, &event);
#endif // !_WIN32
	}

	void AWEpoll::HandleCloseEvent(epoll_event& event)
	{
		if (event.data.ptr == NULL)
		{
			return;
		}

		stSocketContext* ctx = (stSocketContext*)event.data.ptr;
		int fd = ctx->fd;

		Close(fd);
	}


	
	bool AWEpoll::BindOnAddress(const IPEndPoint& address)
	{
		/* listen on sock_fd, new connection on new_fd */
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_socket == SOCKET_ERROR)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		int opt = 1;
#ifndef _WIN32
		setsockopt(m_socket, SOL_SOCKET, 0, &opt, sizeof(opt));
#else
		setsockopt(m_socket, SOL_SOCKET, 0, (const char*)&opt, sizeof(opt));
#endif
		struct sockaddr_in my_addr; /* my address information */
		memset(&my_addr, 0, sizeof(my_addr));
		my_addr.sin_family = AF_INET; /* host byte order */
		my_addr.sin_port = htons(address.Port); /* short, network byte order */
		if ("" == address.Ip || "localhost" == address.Ip)
		{
			my_addr.sin_addr.s_addr = INADDR_ANY;
		}
		else
		{
			my_addr.sin_addr.s_addr = inet_addr(address.Ip.c_str());
		}
		// 监听地址
		if (::bind(m_socket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		if (listen(m_socket, Backlog) == SOCKET_ERROR)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		return true;
	}
	
	bool AWEpoll::ConnectAddress(const IPEndPoint& address)
	{

	}


	bool AWEpoll::CreateEpoll()
	{
		// Since Linux 2.6.8, the size argument is ignored, but must be greater than zero;
		// and under windows select, it should be same as select size 
		m_epoll_fd = epoll_create(1024);
#ifdef _WIN32
		if (m_epoll_fd == NULL)
#else
		if (m_epoll_fd == -1)
#endif
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		return true;
	}

	bool AWEpoll::AddListenSocketToEpoll()
	{
		struct epoll_event ev;
#ifdef _WIN32
		ev.events = EPOLLIN;
#else
		ev.events = EPOLLIN | EPOLLET; // ET
#endif
		ev.data.fd = m_socket;
		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_socket, &ev) == -1)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}

		return true;
	}

	void AWEpoll::HandleEpollEvent(epoll_event& event)
	{
		if (event.data.fd == m_socket)		// 仅仅建立连接的时候进行判断，因为只有此时fd才和server 的监听fd 相等
		{
			// accept connection
			this->HandleAcceptEvent((int&)m_epoll_fd, event);
		}
		else if (event.events & EPOLLIN)
		{
			// handle readable async
			this->HandleEpollReadableEvent(event);
		}
		else if (event.events & EPOLLOUT)
		{
			// writeable
			this->HandleWritableEvent((int&)m_epoll_fd, event);
		}
		else
		{
			this->HandleCloseEvent(event);		//无法识别的 event 都直接断线
		}
	}

	SOCKET AWEpoll::AcceptConnectSocket(const SOCKET fd, IPEndPoint& address)
	{
		SOCKET new_fd = 0;
		struct sockaddr_in their_addr; /* connector's address information */
		socklen_t sin_size = sizeof(struct sockaddr_in);

		if ((new_fd = accept(fd, (struct sockaddr*)&their_addr, &sin_size)) == -1)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return SOCKET_ERROR;
		}

		address.Ip = inet_ntoa(their_addr.sin_addr);
		address.Port = their_addr.sin_port;
		return new_fd;
	}

}