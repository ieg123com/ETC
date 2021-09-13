#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"

#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"



#include "demo/handler/Test.h"



using namespace Model;





int main(int argc,char* argv[])
{


	go [=]{
		Model::Init(argc,argv);
	{
		//Model::Hotfix hotfix;
		try
		{
			//hotfix.Load("hotfix.dll");
			//hotfix.Init(Model::GetGlobalVar());

			LOG_INFO("==============================");



			
			Game::Event().Publish<SystemEvent::AppStart&>(SystemEvent::AppStart());



			TimerComponent::Instance->RegisterOnceTimer(1000, ::Hotfix::StartTest);
			TimerComponent::Instance->RegisterRepeatedTimer(500, [] {LOG_INFO("wait"); });

			co::CoMutex lock;
			TimerComponent::Instance->RegisterRepeatedTimer(1000, [&] {
				LOG_INFO("start timer");
				lock.lock();
				co_sleep(10000);
				lock.unlock();
				LOG_INFO("over timer");

				});


			LOG_INFO("�����������������ɹ�");
			while (true)
			{
				try {
					Model::Game::Event().Update();
					Model::Game::Event().LateUpdate();
					co_sleep(50);
				}
				catch (std::exception& e)
				{
					LOG_ERROR("����ʱ���� {}", e.what());
				}
				catch (...)
				{
					LOG_ERROR("����ʱ����δ֪����");
				}
			}
			
		}
		catch (std::exception& e)
		{
			LOG_ERROR("{}", e.what());
			return;
		}
		catch (...)
		{
			LOG_ERROR("��������ʱ����λ�ô������������Ƿ���ȷ��");
		}
	


	}

	};


	co_sched.Start();
	return 0;
}