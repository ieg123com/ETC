#include "coroutine.h"

#include "base/log/log.h"
#include "base/init.h"
#include "etc/etc.h"
#include "net/NetworkComponent.h"
#include "module/memory/MemorySplit.h"
#include "model/module/message/NetInnerComponent.h"
#include "model/module/message/NetOuterComponent.h"
#include <stdio.h>
//#include "CircularBuffer.h"

using namespace std;
using namespace Model;

class Scene :
	public GEntity
{

};


static const uint16_t port = 80;


std::shared_ptr<Scene> g_scene;

void network_server()
{
	if (g_scene->AddComponent<NetOuterComponent>()->Listen(80))
	{
		LOG_INFO("开启成功");
	}
	else {
		LOG_ERROR("失败");
	}
}



void network_client()
{
	co_sleep(1000);
	auto client_net = g_scene->AddComponent<NetInnerComponent>();
	client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
	for (int i = 0; i < 10; ++i)
	{
		client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
	}

	
// 	session_3->Dispose();
// 	session_2->Dispose();
// 	session_1->Dispose();

	
}


void network()
{
	if (g_scene->AddComponent<NetOuterComponent,const IPEndPoint&>("127.0.0.1:80"))
	{
		LOG_INFO("开启成功");
	}
	else {
		LOG_ERROR("失败");
	}
	auto client_net = g_scene->AddComponent<NetInnerComponent>();
	client_net->Connect("127.0.0.1:80")->Send("Holle this Client!", 19);
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
	MemorySplit	split;

	char str[] = "0123456789[]";

	uint16_t pack_size = sizeof(str);

	for (int row = 0; row < 10; ++row)
	{
		for (int i = 0; i < 10; ++i)
		{
			//split.AddData((char*)&pack_size, sizeof(pack_size));
			split.AddData(str, sizeof(str));
			split.AddData(str, sizeof(str));
		}
		LOG_INFO("开始解析");
		while (split.Unpack())
		{
			LOG_INFO(" [{}] size:{} data:{}",row, split.Data.size(),split.Data.c_str());
		}
	}


	

	while (true)
	{
		LOG_INFO("wait...");
		co_sleep(2000);
	}





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
		LOG_INFO("tick...");
		co_sleep(200);
	}
}


int main(int argc, char* argv[])
{
	Model::Init(argc,argv);
	g_scene = ObjectFactory::Create<Scene>();
// 	go network_server;
// 	go network_client;
//	go network;
	//go echo_server;
	//go test;
	go channel_test;
	//go client;
	go tick;

	co_sched.Start();

	LOG_WARN("over");
	return 0;
}

