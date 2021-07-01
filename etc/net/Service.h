#pragma once
#include "etc.h"
#include "NetDefines.h"
#include "coroutine.h"




class Service:
	public GEntity
{
	friend class Session;
	friend class NetworkComponent;

	typedef co::ConditionVariableAnyT<void*> cond_t;
public:
	template<typename T>
	static std::shared_ptr<Service> Create(const NetworkType type);



	Service() {
		CanEverAwake = true;
	}


	virtual bool Listen(const uint16_t port) = 0;

	virtual std::shared_ptr<Session> Connect(const std::string& ip, const uint16_t port) = 0;



	virtual void Send(const FD fd, const char* data, const size_t len) = 0;

	virtual void Close(const FD fd) = 0;


public:

	NetworkType GetNetworkType() const { return m_network_type; }

protected:
	virtual void Awake() override;

	virtual void Destroy() override;

	// 服务类型
	NetworkType	m_network_type;

	
	// 回调
	std::function<void(std::shared_ptr<Session>&)>					OnConnectComplete;
	std::function<void(std::shared_ptr<Session>&)>					OnAccept;
	std::function<void(std::shared_ptr<Session>&, char*, size_t)>	OnRead;
	std::function<void(std::shared_ptr<Session>&)>					OnDisconnect;

protected:
	// 等待关闭
	// 调用后，当前协程将会挂起。
	// 只有再次调用 CloseComplete 后，才会恢复运行
	void WaitClose();
	// 关闭完成，当socket关闭处理完成后调用
	void CloseComplete();

private:
	// 设置为关闭的
	bool	m_closed;

	cond_t	m_cq;
};


template<typename T>
std::shared_ptr<Service> Service::Create(const NetworkType type)
{
	static_assert(std::is_base_of<Service, T>::value,
		"The create object must inherit 'Service'");
	auto ser = ObjectFactory::Create<T>();
	ser->m_network_type = type;
	return ser;
}