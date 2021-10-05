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

		struct stSocketContext
		{
			SOCKET	fd;
		};


		EpollType		m_type;

		EpollStatus		m_status;
		// 记录已经连接的Socket
		std::unordered_map<int, stSocketContext*>	m_socket_ctx;


		const size_t	Backlog = 1000;
		const size_t	MaxEvents = 1024;

	public:
		int			LastError;
		std::string	LastErrorMsg;



		AWEpoll();




	private:

		void OnEpollAccept()



	private:



		
		// 处理连接事件
		void HandleAcceptEvent(int epoll_fd, epoll_event& event);
		// 处理读取事件
		void HandleEpollReadableEvent(epoll_event& event);
		// 处理写入事件
		void HandleWritableEvent(int epoll_fd, epoll_event& event);


		// 绑定地址
		bool BindOnAddress(const IPEndPoint& address);
		// 连接地址
		bool ConnectAddress(const IPEndPoint& address);


		bool CreateEpoll();
		bool AddListenSocketToEpoll();
		// 处理epoll事件
		void HandleEpollEvent(epoll_event& event);



		SOCKET	m_socket;

#ifndef _WIN32
		int	m_epoll_fd;
#else
		HANDLE	m_epoll_fd;
#endif

	};


}