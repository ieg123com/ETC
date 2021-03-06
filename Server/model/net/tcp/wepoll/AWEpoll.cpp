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
#include "module/memory/Loop.h"


#define AWEPOLL_ERROR(err_code,err_msg) {LastError = err_code;LastErrorMsg = err_msg;LastErrorFunction = __FUNCTION__;LastErrorLine = __LINE__;}



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
	}


	bool AWEpoll::AddSocketCtx(AWEpoll::stSocketContext* ctx)
	{
		return m_socket_ctx.emplace(ctx->fd, ctx).second;
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

	IPEndPoint AWEpoll::GetIPEndPointTry(const int32_t fd)const
	{
		auto found = m_socket_ctx.find(fd);
		if (found == m_socket_ctx.end())
		{
			throw std::exception(std::format("没有找到 IPEndPoint ,fd = %d", fd).c_str());
		}
		return found->second->Address;
	}

	AWEpoll::AWEpoll()
	{
		m_type = EpollType::Server;
		m_status = EpollStatus::STOPPED;
		m_socket = SOCKET_ERROR;
		m_epoll_fd = nullptr;
		m_is_disposed = false;
		m_events = nullptr;
	}

	bool AWEpoll::Listen(const IPEndPoint& address)
	{
		m_type = EpollType::Server;
		if (!CreateEpoll() ||
			!BindOnAddress(address) ||
			!AddListenSocketToEpoll())
		{
			__Dispose();
			return false;
		}
		RemoteAddress = address;
		m_status = EpollStatus::RUNNING;
		if (OnComplete)OnComplete(*this);
		return true;
	}

	bool AWEpoll::Connect(const IPEndPoint& address)
	{
		m_type = EpollType::Connect;
		if (!CreateEpoll() ||
			!ConnectAddress(address) ||
			!AddListenSocketToEpoll())
		{
			__Dispose();
			return false;
		}
		RemoteAddress = address;
		m_status = EpollStatus::RUNNING;
		if (OnComplete)OnComplete(*this);
		OnEpollConnectComplete();
		return true;
	}

	void AWEpoll::Disconnect(const SOCKET fd)
	{
		if (m_type == EpollType::Server)
		{
			auto ctx = GetSocketCtx(fd);
			if (ctx == nullptr)return;

			OnEpollCloseEvent(fd);

			RemoveSocketCtx(fd);
			delete ctx;
		}

		__Disconnect(fd);
	}

	void AWEpoll::Dispose()
	{
		if (IsDisposed())return;
		m_is_disposed = true;
		if (m_status != EpollStatus::RUNNING)return;
		// 服务开启中

		__Dispose();
		m_status = EpollStatus::STOPPED;
	}

	bool AWEpoll::Send(const int32_t fd, const char* data, const size_t len)
	{
		size_t count = len;
		const char* pos = data;

		int ret = send(fd, pos, count, 0);
		if (ret < 0)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		return true;
	}

	bool AWEpoll::Send(const char* data, const size_t len)
	{
		return Send(m_socket, data, len);
	}


	void AWEpoll::Update()
	{
		if (m_status == EpollStatus::STOPPED)return;
		if (m_events == nullptr)
		{
			m_events = new epoll_event[MaxEvents];
		}
		int num_events = epoll_wait(m_epoll_fd, m_events, MaxEvents, 0);
		if (num_events == -1)
		{
			if (errno == EINTR)
			{ /*The call was interrupted by a signal handler*/
				return;
			}
			return;
		}
		for (int i = 0; i < num_events; ++i)
		{
			HandleEpollEvent(m_events[i]);
		}

	}

	void AWEpoll::OnEpollConnectComplete()
	{
		if (OnConnect)OnConnect(*this,m_socket);
	}

	void AWEpoll::OnEpollAcceptEvent(int32_t fd)
	{
		if (OnAccept)OnAccept(*this,fd);
	}

	int AWEpoll::OnEpollReadableEvent(int32_t fd)
	{
		auto data = Loop<std::vector<char>>::Instance().Fetch();
		data->resize(READ_BUFFER_SIZE);
		int read_size = recv(fd, data->data(), READ_BUFFER_SIZE, 0);
		if (read_size == SOCKET_ERROR && errno == EINTR) {
			AWEPOLL_ERROR(errno, strerror(errno));
			return READ_CONTINUE;
		}
		if (read_size == SOCKET_ERROR /* io err*/ || read_size == 0 /* close */)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return READ_CLOSE;
		}
		data->resize(read_size);
		if (OnRead)OnRead(*this, fd, data);
		return READ_OVER;
	}

	int AWEpoll::OnEpollWritableEvent(int32_t fd)
	{
		if (OnWrite)OnWrite(*this, fd);
		return WRITE_CONN_ALIVE;
	}

	void AWEpoll::OnEpollCloseEvent(int32_t fd)
	{
		if (OnDisconnect)OnDisconnect(*this, fd);
	}

	void AWEpoll::OnEpollErrorEvent()
	{

	}


	void AWEpoll::__Dispose()
	{
		if (m_type == EpollType::Server)
		{
			// 断开所有连接
			std::vector<SOCKET> closed_fd;
			for (auto& ctx : m_socket_ctx)
			{
				closed_fd.emplace_back(ctx.first);
			}
			for (auto fd : closed_fd)
			{
				Disconnect(fd);
			}
		}
		if (m_socket != SOCKET_ERROR)
		{
			if (m_type == EpollType::Connect)
			{
				OnEpollCloseEvent(m_socket);
			}
			__Disconnect(m_socket);
			m_socket = SOCKET_ERROR;
		}
		if (m_epoll_fd == nullptr)
		{
			epoll_close(m_epoll_fd);
			m_epoll_fd = nullptr;
		}
	}

	void AWEpoll::__Disconnect(const int32_t fd)
	{
		epoll_event disconnectEvent;
		disconnectEvent.events = EPOLLIN | EPOLLOUT;
		epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, &disconnectEvent);

#ifndef _WIN32
		int ret = close(fd);
#else
		int ret = closesocket(fd);
#endif

		if (ret != 0)
		{
			AWEPOLL_ERROR(errno, std::format("error:(%s) connect close complete which fd: %d, ret: %d", strerror(errno), fd, ret));
			return;
		}
	}

	void AWEpoll::HandleAcceptEvent(const int32_t epoll_fd, epoll_event& event)
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

		OnEpollAcceptEvent(ctx->fd);

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
		int fd = 0;
		if (m_type == EpollType::Server)
		{
			auto ctx = (stSocketContext*)event.data.ptr;
			fd = ctx->fd;
		}
		else {
			fd = m_socket;
		}
		
		int ret = OnEpollReadableEvent(fd);
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

	void AWEpoll::HandleWritableEvent(const int32_t epoll_fd, epoll_event& event)
	{
		int fd = 0;
		if (m_type == EpollType::Server)
		{
			auto ctx = (stSocketContext*)event.data.ptr;
			fd = ctx->fd;
		}
		else {
			fd = m_socket;
		}

		int ret = OnEpollWritableEvent(fd);
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
		int fd = 0;
		if (m_type == EpollType::Server)
		{
			stSocketContext* ctx = (stSocketContext*)event.data.ptr;
			fd = ctx->fd;
		}
		else {
			fd = m_socket;
		}

		Disconnect(fd);
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
		// 连接地址
		if (connect(m_socket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		{
			AWEPOLL_ERROR(errno, strerror(errno));
			return false;
		}
		return true;
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
		if (m_type == EpollType::Server && event.data.fd == m_socket)		// 仅仅建立连接的时候进行判断，因为只有此时fd才和server 的监听fd 相等
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