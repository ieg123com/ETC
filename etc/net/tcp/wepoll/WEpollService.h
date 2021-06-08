#pragma once
#include "net/Service.h"
#include "error/error_content.h"

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


enum class EpollStatus : uint8_t
{
	EPOLL_RUNNING = 0,
	EPOLL_STOPPED
};

// local server info
struct stAddressInfo
{
	std::string serverIp;
	uint16_t port;
	uint32_t maxEvents;
	uint32_t backlog;
	uint32_t WorkerThreadTaskMax;
	uint32_t timeCheckAcceptClient;

	stAddressInfo()
	{
		serverIp = "";
		port = 0;
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

class WEpollService :
	public Service
{
public:
	WEpollService();


	virtual bool Listen(const uint16_t port) override;

	virtual std::shared_ptr<Session> Connect(const std::string& ip, const uint16_t port) override;



	virtual void Send(const FD fd, const char* data, const size_t len) override;

protected:

	virtual void Awake() override;

	virtual void Destroy() override;

	
private:

	int OnEpollAcceptEvent(stSocketContext* ctx);
	int OnEpollReadableEvent(stSocketContext* ctx, epoll_event& epoll_event);
	int OnEpollWriteableEvent(stSocketContext* ctx);
	int OnEpollCloseEvent(stSocketContext* ctx);

private:

	int SetNonBlocking(FD fd);

	bool BindOnAddress(const stAddressInfo& addressInfo);

	bool ConnectAddress(const stAddressInfo& addressInfo);


	FD AcceptConnectSocket(FD sockfd, std::string& client_ip);

	void HandleAcceptEvent(FD& epollfd, epoll_event& event);
	void HandleEpollReadableEvent(epoll_event& event);
	void HandleWriteableEvent(FD& epollfd, epoll_event& event);
	void DisconnectOneClient(FD clientFD);

	bool AddListenSocketToEpoll();
	void HandleEpollEvent(epoll_event& e);
	bool CreateEpoll();

	void StartEpollEventLoop();
	void StartClientEventLoop(std::shared_ptr<Session> session);

	bool StartEpollServer();



	void CloseAndReleaseOneEvent(epoll_event& epoll_event);

private:

	EpollStatus		m_epoll_status;
	stAddressInfo	m_address_info;
	int				m_listened_socket;

#ifndef _WIN32
	int m_epollfd;
#else
	HANDLE m_epollfd;
#endif


};