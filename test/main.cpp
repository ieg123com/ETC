#include "coroutine.h"
#pragma comment(lib,"ws2_32.lib")
#include "wepoll.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

#include "log/log.h"
#include "etc.h"
#include "net/NetworkComponent.h"
#include <stdio.h>

using namespace std;

class Scene :
	public GEntity
{

};


static const uint16_t port = 80;


std::shared_ptr<Scene> g_scene;

void network_server()
{
	if (g_scene->AddComponent<NetworkComponent>()->Listen(81))
	{
		LOG_INFO("�����ɹ�");
	}
	else {
		LOG_ERROR("ʧ��");
	}
}


class ClientNetworkComponent : public NetworkComponent
{

};

void network_client()
{
	co_sleep(1000);
	auto client_net = g_scene->AddComponent<ClientNetworkComponent>();

	auto session_1 = client_net->Connect("127.0.0.1", 81);
	auto session_2 = client_net->Connect("127.0.0.1", 81);
	auto session_3 = client_net->Connect("127.0.0.1", 81);
	
	session_3->Dispose();
	session_2->Dispose();
	session_1->Dispose();

	
}

// std::vector<co::Channel<std::string>>	g_channel;
// typedef co::ConditionVariableAnyT<void*> cond_t;
// cond_t g_cond;
int ret_num()
{
	return 100;
}


void test()
{
	while (true)
	{
		LOG_INFO("wait...");
		co_sleep(2000);
	}

	go_stack ret_num;



// 	co::FakeLock lock;
// 
// 	LOG_INFO("Start");
// 	g_cond.wait(lock, nullptr, [&](size_t size)-> typename cond_t::CondRet {
// 		typename cond_t::CondRet ret{ true,true };
// 
// 
// 		return ret;
// 		});
// 
// 	LOG_INFO("End");
	
}
class A
{
public:
	std::mutex m_lock;

	~A() {
		//m_lock.unlock();
		assert(m_lock.try_lock());
	}
};

void channel_test()
{
	{
		//co_chan<std::string> g_channel;
		co::Channel<std::string>	g_channel(10);
		//A a;
		LOG_INFO("1");
		g_channel << "123";
		LOG_INFO("2");
		std::string str;
		g_channel >> str;

		LOG_INFO("str {}", str.c_str());
		//LOG_INFO("lock");
		//g_lock.lock();
		//assert(g_lock.try_lock());
		//LOG_INFO("unlock");


	}



}


int main()
{
	g_scene = ObjectFactory::Create<Scene>();
	//go network_server;
	//go network_client;
	//go echo_server;
	go test;
	//go channel_test;
	//go client;

	co_sched.Start();

	LOG_WARN("over");
	return 0;
}

