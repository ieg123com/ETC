#include "AWEpoll.h"


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


	AWEpoll::AWEpoll()
	{
		m_type = EpollType::Server;
		m_status = EpollStatus::STOPPED;
		m_socket = SOCKET_ERROR;
		m_epoll_fd = nullptr;


	}






	void AWEpoll::HandleAcceptEvent(int epoll_fd, epoll_event& event)
	{

	}

	void AWEpoll::HandleEpollReadableEvent(epoll_event& event)
	{

	}

	void AWEpoll::HandleWritableEvent(int epoll_fd, epoll_event& event)
	{

	}


	
	bool AWEpoll::BindOnAddress(const IPEndPoint& address)
	{
		/* listen on sock_fd, new connection on new_fd */
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_socket == SOCKET_ERROR)
		{
			LastError = errno;
			LastErrorMsg = strerror(errno);
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
			LastError = errno;
			LastErrorMsg = strerror(errno);
			return false;
		}
		if (listen(m_socket, Backlog) == SOCKET_ERROR)
		{
			LastError = errno;
			LastErrorMsg = strerror(errno);
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
			LastError = errno;
			LastErrorMsg = strerror(errno);
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
			LastError = errno;
			LastErrorMsg = strerror(errno);
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
			LOG_WARN("unknown events : {}", event.events);
			CloseAndReleaseOneEvent(event);		//无法识别的 event 都直接断线
		}
	}
}