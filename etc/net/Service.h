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

	// ��������
	NetworkType	m_network_type;

	
	// �ص�
	std::function<void(std::shared_ptr<Session>&)>					OnConnectComplete;
	std::function<void(std::shared_ptr<Session>&)>					OnAccept;
	std::function<void(std::shared_ptr<Session>&, char*, size_t)>	OnRead;
	std::function<void(std::shared_ptr<Session>&)>					OnDisconnect;

protected:
	// �ȴ��ر�
	// ���ú󣬵�ǰЭ�̽������
	// ֻ���ٴε��� CloseComplete �󣬲Ż�ָ�����
	void WaitClose();
	// �ر���ɣ���socket�رմ�����ɺ����
	void CloseComplete();

private:
	// ����Ϊ�رյ�
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