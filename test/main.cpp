#include "coroutine.h"

#include "base/log/log.h"
#include "base/init.h"
#include "etc/etc.h"
//#include "net/NetworkComponent.h"
#include "module/memory/MemorySplit.h"
#include "model/module/message/NetInnerComponent.h"
#include "model/module/message/NetOuterComponent.h"
#define LIBASYNC_NUM_THREADS 20
#include "model/base/async/async.h"
#include "model/other/time/Time.h"
#include "net/tcp/wepoll/AWEpoll.h"
#include <stdio.h>
#include <stdint.h>
//#include "CircularBuffer.h"

using namespace std;
using namespace Model;

class Scene :
	public GEntity
{

};


static const uint16_t port = 80;


std::shared_ptr<Scene> g_scene;
// 
// void network_server()
// {
// 	if (g_scene->AddComponent<NetOuterComponent>()->Listen(80))
// 	{
// 		LOG_INFO("开启成功");
// 	}
// 	else {
// 		LOG_ERROR("失败");
// 	}
// }



// void network_client()
// {
// 	co_sleep(1000);
// 	auto client_net = g_scene->AddComponent<NetInnerComponent>();
// 	client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
// 	}
// 
// 	
// // 	session_3->Dispose();
// // 	session_2->Dispose();
// // 	session_1->Dispose();
// 
// 	
// }


// void network()
// {
// 	if (g_scene->AddComponent<NetOuterComponent,const IPEndPoint&>("127.0.0.1:80"))
// 	{
// 		LOG_INFO("开启成功");
// 	}
// 	else {
// 		LOG_ERROR("失败");
// 	}
// 	auto client_net = g_scene->AddComponent<NetInnerComponent>();
// 	client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
// }
// std::vector<co::Channel<std::string>>	g_channel;
// typedef co::ConditionVariableAnyT<void*> cond_t;
// cond_t g_cond;


void EpollAccept(AWEpoll& self,int fd) {
	LOG_INFO("Accept IP:{}",self.GetIPEndPointTry(fd).ToString());

}

void EpollRead(AWEpoll& self, int fd, const std::shared_ptr<std::string>& data) {
	LOG_INFO("Read IP:{}", self.GetIPEndPointTry(fd).ToString());
	LOG_INFO("Read data:{}", data->c_str());
	char data2[] = "This Server";
	self.Send(fd, data2, sizeof(data2));
	LOG_INFO("EpollRead end");
}

void EpollWrite(AWEpoll& self, int fd) {
	LOG_INFO("Write IP:{}", self.GetIPEndPointTry(fd).ToString());
}

void EpollDisconnect(AWEpoll& self, int fd) {
	LOG_INFO("Disconnect IP:{}", self.GetIPEndPointTry(fd).ToString());
}



void CEpollConnectComplete(AWEpoll& self, int fd) {

	LOG_WARN("ConnectComplete");
}

void CEpollAccept(AWEpoll& self, int fd) {
	LOG_WARN("Accept");
}

void CEpollRead(AWEpoll& self, int fd, const std::shared_ptr<std::string>& data) {
	LOG_WARN("Read");
	LOG_WARN("Read data:{}", data->c_str());
}

void CEpollWrite(AWEpoll& self, int fd) {
	LOG_WARN("Write");
	self.Dispose();
}

void CEpollDisconnect(AWEpoll& self, int fd) {
	LOG_WARN("Disconnect");
}

int ret_num()
{
	return 100;
}


void test()
{
	AWEpoll epoll;
	epoll.OnAccept = EpollAccept;
	epoll.OnRead = EpollRead;
	epoll.OnWrite = EpollWrite;
	epoll.OnDisconnect = EpollDisconnect;


	epoll.Listen("127.0.0.1:80");
	while (true)
	{
		co_sleep(1);
		epoll.Update();
	}
	
}

void test2()
{
	AWEpoll epoll;
	epoll.OnAccept = CEpollAccept;
	epoll.OnRead = CEpollRead;
	epoll.OnWrite = CEpollWrite;
	epoll.OnDisconnect = CEpollDisconnect;


	epoll.Connect("127.0.0.1:80");

	char data[] = "hello wepoll";
	epoll.Send(data, sizeof(data));
	while (true)
	{
		co_sleep(1);
		epoll.Update();
	}

}

void channel_test()
{
	{
		//co_chan<std::string> g_channel;
		co::Channel<std::string>	channel(1);
		//A a;
		//LOG_INFO("1");
		LOG_INFO("ok 0");
		channel << "123";
		LOG_INFO("ok 1");
		channel << "456";
		LOG_INFO("ok 2");
		channel << "789";
		LOG_INFO("ok 3");
		channel << "012";
		LOG_INFO("ok 4");
		std::string ctx;
		//LOG_WARN("TimedPop {}", channel.TimedPop(ctx, std::chrono::milliseconds(1000)));
		
		//LOG_INFO("ok {}", g_channel.TryPush("123"));
		//LOG_INFO("ok {}", g_channel.TryPush("123"));

		//LOG_INFO("2");
		//std::string str;
		
		//std::mutex lock;
		//lock.lock();
		//LOG_INFO("str {}", str.c_str());
		//LOG_INFO("lock");
		//lock.lock();
		//LOG_INFO("try_lock {}", );
		//assert(false);
		//LOG_INFO("unlock");

		//lock.unlock();
	}



}

void tick()
{

	while (true)
	{
		//LOG_INFO("tick...");
		co_sleep(200);
	}
}


int main(int argc, char* argv[])
{
	Time::TimeBeginPeriod(1);
	Model::Init(argc,argv);
	g_scene = ObjectFactory::Create<Scene>();
	Model::async::Scheduler::Instance->Start();

// 	go network_server;
// 	go network_client;
//	go network;
	//go echo_server;
	go test;
	go test2;
	//go channel_test;
	//go client;
	go tick;


	co_sched.Start();

	LOG_WARN("over");
	return 0;
}

