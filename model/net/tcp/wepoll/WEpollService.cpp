#include "WEpollService.h"
#include "etc/etc.h"

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

#include "net/Session.h"


// 异步 epoll wait
int co_epoll_wait(int socket,
	HANDLE ephnd,
	struct epoll_event* events,
	int maxevents,
	int timeout)
{
#if _WIN32
	timeval tv = { timeout / 1000, (timeout % 1000) * 1000 };

	fd_set readfds, exceptfds;
	FD_ZERO(&readfds);
	FD_SET(socket, &readfds);
	FD_ZERO(&exceptfds);
	FD_SET(socket, &exceptfds);
	int n = select(0, &readfds, nullptr, &exceptfds, &tv);

	return epoll_wait(ephnd, events, maxevents, 0);
#else
	return epoll_wait(ephnd, events, maxevents, timeout);
#endif
}


namespace Model
{
	class WEpollServiceAwakeSystem :public AwakeSystem<WEpollService>
	{
	public:
		virtual void Awake(const std::shared_ptr<WEpollService>& self) override
		{
			self->Awake();
		}
	};
	REF(WEpollServiceAwakeSystem, ObjectSystem);

	class WEpollServiceDestroySystem : public DestroySystem<WEpollService>
	{
	public:
		virtual void Destroy(const std::shared_ptr<WEpollService>& self) override
		{
			self->Destroy();
		}
	};
	REF(WEpollServiceDestroySystem, ObjectSystem);


	WEpollService::WEpollService()
	{
#ifdef _WIN32
		WSADATA wsadata;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
#endif
	}


	bool WEpollService::Listen(const IPEndPoint& address)
	{

		m_address_info.address = address;

		if (!StartEpollServer())
		{
			return false;
		}

		m_epoll_status = EpollStatus::EPOLL_RUNNING;
		go std::bind(&WEpollService::StartEpollEventLoop, this);

		return true;
	}

	std::shared_ptr<Session> WEpollService::Connect(const IPEndPoint& address)
	{
		if (m_listened_socket != -1)
		{
			LOG_ERROR("当前组件已经在运作了");
			return false;
		}

		m_address_info.address = address;

		if (!ConnectAddress(m_address_info))
		{
			return nullptr;
		}

		// 创建新会话
		stSocketContext* ctx = new stSocketContext();
		ctx->session = ObjectFactory::Create<Session>();
		ctx->session->SessionId = m_listened_socket;
		ctx->session->Address = address;
		ctx->session->__service = Get<Service>();
		__AddSocketCtx(m_listened_socket, ctx);

		m_epoll_status = EpollStatus::EPOLL_RUNNING;
		go std::bind(&WEpollService::StartClientEventLoop, this, ctx->session);

		return ctx->session;
	}



	void WEpollService::Send(const SessionID fd, const char* data, const size_t len)
	{
		send(fd, data, len, 0);
	}

	void WEpollService::Close(const SessionID fd)
	{
		if (m_network_type == NetworkType::Server)
		{
			auto ctx = __GetSocketCtx(fd);
			if (!ctx)
			{
				LOG_ERROR("close fd failed! fd:{}", fd);
				return;
			}
			__RemoveSocketCtx(fd);

			OnEpollCloseEvent(ctx);

			DisconnectOneClient(fd);

			delete ctx;
		}
		else if (m_network_type == NetworkType::Client)
		{

		}

	}


	void WEpollService::Awake()
	{
		Service::Awake();

		m_epoll_status = EpollStatus::EPOLL_STOPPED;
#ifdef _WIN32
		m_epollfd = INVALID_HANDLE_VALUE;
#else
		m_epollfd = -1;
#endif // _WIN32

		m_listened_socket = SOCKET_ERROR;
	}

	void WEpollService::Destroy()
	{

		if (m_epoll_status == EpollStatus::EPOLL_RUNNING)
		{
			m_epoll_status = EpollStatus::EPOLL_STOPPED;

			if (m_network_type == NetworkType::Server)
			{
				// 断开所有连接

				auto all_socket = m_all_socket_ctx;
				stSocketContext* ctx = nullptr;
				for (auto& item : all_socket)
				{
					ctx = item.second;

					OnEpollCloseEvent(ctx);

					DisconnectOneClient(item.first);

					__RemoveSocketCtx(item.first);
					delete ctx;
				}


				if (m_epollfd)
				{
					epoll_close(m_epollfd);
				}
			}
			else if (m_network_type == NetworkType::Client)
			{

#ifdef _WIN32
				int ret = closesocket(m_listened_socket);
#else
				int ret = close(m_listened_socket);
#endif
			}
			WaitClose();
			m_epollfd = INVALID_HANDLE_VALUE;
			m_listened_socket = SOCKET_ERROR;
		}
		Service::Destroy();
	}

	int WEpollService::OnEpollAcceptEvent(stSocketContext* ctx)
	{
		if (OnAccept)
		{
			OnAccept(ctx->session);
		}
		return 0;
	}

	int WEpollService::OnEpollReadableEvent(stSocketContext* ctx, epoll_event& epoll_event)
	{

		int fd = ctx->session->SessionId;

		static char read_buffer[READ_BUFFER_SIZE];
		//memset(read_buffer, 0, READ_BUFFER_SIZE);

		int read_size = recv(fd, read_buffer, READ_BUFFER_SIZE, 0);
		if (read_size == SOCKET_ERROR && errno == EINTR) {
			return READ_CONTINUE;
		}
		if (read_size == SOCKET_ERROR /* io err*/ || read_size == 0 /* close */)
		{
			return READ_CLOSE;
		}

		if (OnRead)
		{
			OnRead(ctx->session, read_buffer, read_size);
		}

		return READ_OVER;
	}

	int WEpollService::OnEpollWriteableEvent(stSocketContext* ctx)
	{
		return 0;

	}

	int WEpollService::OnEpollCloseEvent(stSocketContext* ctx)
	{
		if (OnDisconnect)
		{
			OnDisconnect(ctx->session);
		}
		return 0;

	}

	int WEpollService::SetNonBlocking(SessionID fd)
	{
#ifndef _WIN32
		int flags;
		if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
			flags = 0;
		return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
		unsigned long flags = 1; /* 这里根据需要设置成0或1 */
		return ioctlsocket(fd, FIONBIO, &flags);
#endif
	};

	bool WEpollService::BindOnAddress(const stAddressInfo& addressInfo)
	{
		/* listen on sock_fd, new connection on new_fd */
		m_listened_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_listened_socket == -1)
		{
			LOG_ERROR("socket error: {}", strerror(errno));
			return false;
		}
		int opt = 1;
#ifndef _WIN32
		setsockopt(m_listened_socket, SOL_SOCKET, 0, &opt, sizeof(opt));
#else
		setsockopt(m_listened_socket, SOL_SOCKET, 0, (const char*)&opt, sizeof(opt));
#endif
		struct sockaddr_in my_addr; /* my address information */
		memset(&my_addr, 0, sizeof(my_addr));
		my_addr.sin_family = AF_INET; /* host byte order */
		my_addr.sin_port = htons(addressInfo.address.Port); /* short, network byte order */
		if ("" == addressInfo.address.Ip || "localhost" == addressInfo.address.Ip)
		{
			my_addr.sin_addr.s_addr = INADDR_ANY;
		}
		else
		{
			my_addr.sin_addr.s_addr = inet_addr(addressInfo.address.Ip.c_str());
		}
		// 监听地址
		if (::bind(m_listened_socket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		{
			LOG_ERROR("bind error: {}", strerror(errno));
			return false;
		}
		if (listen(m_listened_socket, addressInfo.backlog) == SOCKET_ERROR)
		{
			LOG_ERROR("listen error: {}", strerror(errno));
			return false;
		}
		return true;
	}


	bool WEpollService::ConnectAddress(const stAddressInfo& addressInfo)
	{
		/* listen on sock_fd, new connection on new_fd */
		m_listened_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_listened_socket == -1)
		{
			LOG_ERROR("socket error: {}", strerror(errno));
			return false;
		}
		int opt = 1;
#ifndef _WIN32
		setsockopt(m_listened_socket, SOL_SOCKET, 0, &opt, sizeof(opt));
#else
		setsockopt(m_listened_socket, SOL_SOCKET, 0, (const char*)&opt, sizeof(opt));
#endif
		struct sockaddr_in my_addr; /* my address information */
		memset(&my_addr, 0, sizeof(my_addr));
		my_addr.sin_family = AF_INET; /* host byte order */
		my_addr.sin_port = htons(addressInfo.address.Port); /* short, network byte order */
		if ("" == addressInfo.address.Ip || "localhost" == addressInfo.address.Ip)
		{
			my_addr.sin_addr.s_addr = INADDR_ANY;
		}
		else
		{
			my_addr.sin_addr.s_addr = inet_addr(addressInfo.address.Ip.c_str());
		}
		// 连接地址
		if (connect(m_listened_socket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		{
			LOG_ERROR("connect error:{} {}", WSAGetLastError(), strerror(errno));
			return false;
		}
		return true;
	}

	SessionID WEpollService::AcceptConnectSocket(SessionID sockfd, std::string& client_ip)
	{
		SessionID new_fd = 0;
		struct sockaddr_in their_addr; /* connector's address information */
		socklen_t sin_size = sizeof(struct sockaddr_in);

		if ((new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1)
		{
			LOG_ERROR("accept error: {}", strerror(errno));
			return -1;
		}

		client_ip = inet_ntoa(their_addr.sin_addr);
		return new_fd;
	}

	void WEpollService::HandleAcceptEvent(SessionID& epollfd, epoll_event& event)
	{
		int sockfd = event.data.fd;

		std::string client_ip = "";
		int conn_sock = AcceptConnectSocket(sockfd, client_ip);
		if (-1 == conn_sock)
		{
			LOG_ERROR("AcceptConnectSocket failed!");
			return;
		}
		if (0 != SetNonBlocking(conn_sock))
		{
			LOG_ERROR("set conn sock nonblocking failed!");
			return;
		}


		// 创建新会话
		stSocketContext* ctx = new stSocketContext();
		ctx->session = ObjectFactory::Create<Session>();
		ctx->session->SessionId = conn_sock;
		ctx->session->Address.Ip = std::move(client_ip);
		ctx->session->__service = Get<Service>();

		if (!__AddSocketCtx(conn_sock, ctx))
		{
			LOG_ERROR("abnormal fd allocation!");
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

		if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, conn_sock, &conn_sock_ev) == -1)
		{
			LOG_ERROR("epoll_ctl: conn_sock: {}", strerror(errno));
			CloseAndReleaseOneEvent(event);
			return;
		}
	}


	void WEpollService::HandleEpollReadableEvent(epoll_event& event)
	{
		auto ctx = (stSocketContext*)event.data.ptr;
		int fd = ctx->session->SessionId;


		int ret = OnEpollReadableEvent(ctx, event);

		if (ret == READ_CLOSE)
		{
			CloseAndReleaseOneEvent(event);
			return;
		}
		if (ret == READ_CONTINUE)
		{
			event.events = EPOLLIN | EPOLLONESHOT;
			epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &event);
		}
		else if (ret == READ_OVER)
		{ // READ_OVER
			event.events = EPOLLOUT | EPOLLONESHOT;
			epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &event);
		}
		else
		{
			LOG_ERROR("Unknown read ret: {}", ret);
			return;
		}
	}


	void WEpollService::HandleWriteableEvent(SessionID& epollfd, epoll_event& event)
	{
		auto ctx = (stSocketContext*)event.data.ptr;
		int fd = ctx->session->SessionId;
		//LOG_DEBUG("start write data");

		int ret = OnEpollWriteableEvent(ctx);
		if (ret == WRITE_CONN_CLOSE)
		{
			CloseAndReleaseOneEvent(event);
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
			LOG_ERROR("Unknown write ret: {}", ret);
		}
#ifndef _WIN32
		epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
#else
		epoll_ctl((HANDLE)epollfd, EPOLL_CTL_MOD, fd, &event);
#endif // !_WIN32
	}

	void WEpollService::DisconnectOneClient(SessionID clientFD)
	{
		epoll_event disconnectEvent;
		disconnectEvent.events = EPOLLIN | EPOLLOUT;
		epoll_ctl(m_epollfd, EPOLL_CTL_DEL, clientFD, &disconnectEvent);

#ifndef _WIN32
		int ret = close(clientFD);
#else
		int ret = closesocket(clientFD);
#endif

		if (ret != 0)
		{
			LOG_ERROR("connect close complete which fd: {}, ret: {}", clientFD, ret);
			return;
		}
	}

	bool WEpollService::AddListenSocketToEpoll()
	{
		struct epoll_event ev;
#ifdef _WIN32
		ev.events = EPOLLIN;
#else
		ev.events = EPOLLIN | EPOLLET; // ET
#endif
		ev.data.fd = m_listened_socket;
		if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_listened_socket, &ev) == -1)
		{
			LOG_ERROR("epoll_ctl: listen_sock: {}", strerror(errno));
			return false;
		}

		return true;
	}

	void WEpollService::HandleEpollEvent(epoll_event& e)
	{
		if (e.data.fd == m_listened_socket)		// 仅仅建立连接的时候进行判断，因为只有此时fd才和server 的监听fd 相等
		{
			// accept connection
			this->HandleAcceptEvent((int&)m_epollfd, e);
		}
		else if (e.events & EPOLLIN)
		{
			// handle readable async
			this->HandleEpollReadableEvent(e);
		}
		else if (e.events & EPOLLOUT)
		{
			// writeable
			this->HandleWriteableEvent((int&)m_epollfd, e);
		}
		else
		{
			LOG_WARN("unknown events : {}", e.events);
			CloseAndReleaseOneEvent(e);		//无法识别的 event 都直接断线
		}
	}

	bool WEpollService::CreateEpoll()
	{
		// Since Linux 2.6.8, the size argument is ignored, but must be greater than zero;
		// and under windows select, it should be same as select size 
		m_epollfd = epoll_create(1024);
#ifdef _WIN32
		if (m_epollfd == NULL)
#else
		if (m_epollfd == -1)
#endif
		{
			LOG_ERROR("epoll_create: {}", strerror(errno));
			return false;
		}

		return true;
	}


	void WEpollService::StartEpollEventLoop()
	{
		epoll_event* events = new epoll_event[m_address_info.maxEvents];
		while (m_epoll_status == EpollStatus::EPOLL_RUNNING)
		{
			int fds_num = co_epoll_wait(m_listened_socket, m_epollfd, events, m_address_info.maxEvents, 100);

			if (fds_num == -1)
			{
				if (errno == EINTR)
				{ /*The call was interrupted by a signal handler*/
					continue;
				}
				LOG_ERROR("epoll_wait error: {}", strerror(errno));
				break;
			}
			else if (fds_num == 0)
			{
				continue;
			}

			for (int i = 0; i < fds_num; i++)
			{
				this->HandleEpollEvent(events[i]);
			}

		}
		LOG_INFO("epoll wait loop stop ...");
		if (events != NULL)
		{
			delete[] events;
			events = NULL;
			LOG_WARN("still have events not handle, and loop end");
		}
		CloseComplete();
	}

	void WEpollService::StartClientEventLoop(std::shared_ptr<Session> session)
	{
		static char read_buffer[READ_BUFFER_SIZE];
		timeval timeout;
		timeout.tv_sec = 100 / 1000;
		timeout.tv_usec = 100 % 1000 * 1000;

#if _WIN32
		int sock = m_listened_socket;
#else
		int sock = m_listened_socket + 1;
#endif


		if (OnConnectComplete)
		{
			OnConnectComplete(session);
		}

		while (m_epoll_status == EpollStatus::EPOLL_RUNNING)
		{
			fd_set fd;
			FD_ZERO(&fd);
			FD_SET(sock, &fd);
			int ret = select(sock, &fd, NULL, NULL, &timeout);
			if (ret <= 0)
			{
				continue;
			}

			int read_size = recv(sock, read_buffer, READ_BUFFER_SIZE, 0);
			if (read_size == 0)
			{
				// 连接已断开
				break;
			}
			if (read_size == SOCKET_ERROR)
			{
#ifdef _WIN32
				if (WSAGetLastError() == WSAESHUTDOWN ||
					WSAGetLastError() == WSAECONNRESET ||
					m_epoll_status == EpollStatus::EPOLL_STOPPED)
				{
					// 关闭连接
					break;
				}
				else {
					// 其他错误
					LOG_ERROR("recv error {}", WSAGetLastError());
					continue;
				}
#else
				// 读取数据时发生错误
				// 连接已断开
				break;
#endif
			}

			if (OnRead)
			{
				OnRead(session, read_buffer, read_size);
			}

		}

		if (auto ctx = __GetSocketCtx(m_listened_socket))
		{
			if (OnDisconnect)
			{
				OnDisconnect(ctx->session);
			}
#ifdef _WIN32
			int ret = closesocket(m_listened_socket);
#else
			int ret = close(m_listened_socket);
#endif
			__RemoveSocketCtx(m_listened_socket);
			delete ctx;
		}

		CloseComplete();
	}

	bool WEpollService::StartEpollServer()
	{
		if (m_listened_socket != -1)
		{
			LOG_ERROR("当前组件已经在运作了");
			return false;
		}
		bool ret = true;

		do
		{
			ret = BindOnAddress(m_address_info);
			if (!ret) break;

			ret = CreateEpoll();
			if (!ret) break;

			ret = AddListenSocketToEpoll();
			if (!ret) break;

		} while (0);

		if (!ret)
		{
			return false;
		}

		return true;
	}

	void WEpollService::CloseAndReleaseOneEvent(epoll_event& epoll_event)
	{
		if (epoll_event.data.ptr == NULL)
		{
			return;
		}

		stSocketContext* ctx = (stSocketContext*)epoll_event.data.ptr;
		SessionID fd = ctx->session->SessionId;
		Close(fd);

	}


	bool WEpollService::__AddSocketCtx(const SessionID session_id, stSocketContext* ctx)
	{
		return m_all_socket_ctx.insert(std::make_pair(session_id, ctx)).second;
	}

	bool WEpollService::__RemoveSocketCtx(const SessionID session_id)
	{
		auto found = m_all_socket_ctx.find(session_id);
		if (found == m_all_socket_ctx.end())
		{
			return false;
		}
		m_all_socket_ctx.erase(found);
		return true;
	}

	stSocketContext* WEpollService::__GetSocketCtx(const SessionID session_id) const
	{
		auto found = m_all_socket_ctx.find(session_id);
		if (found == m_all_socket_ctx.end())
		{
			return nullptr;
		}
		return found->second;
	}
}