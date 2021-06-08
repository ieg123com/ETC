/************************************************
 * libgo sample15 debug
*************************************************/
#include "coroutine.h"
#pragma comment(lib,"ws2_32.lib")
#include "wepoll.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

//#include "win_exit.h"
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
		LOG_INFO("¿ªÆô³É¹¦");
	}
	else {
		LOG_ERROR("Ê§°Ü");
	}
}


class ClientNetworkComponent : public NetworkComponent
{

};

void network_client()
{
	auto client_net = g_scene->AddComponent<ClientNetworkComponent>();

	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);
	client_net->Connect("127.0.0.1", 81);


}




void test()
{
	while (1)
	{
		LOG_INFO("Test");
		co_sleep(2000);
	}

}



int main()
{
	g_scene = ObjectFactory::Create<Scene>();

	//go network_server;
	go network_client;
	//go echo_server;
	go test;
	//go client;

    co_sched.Start();
   
	LOG_WARN("over");
    return 0;
}

