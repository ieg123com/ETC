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

	Time::TimeBeginPeriod(1);
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
			//TimerComponent::Instance->RegisterRepeatedTimer(1000, [] {LOG_INFO("wait..."); });

			LOG_INFO("�����������������ɹ�");
			while (true)
			{
				try {
					ThreadSyncContext::Instance->Update();
					Model::Game::Event().Update();
					Model::Game::Event().LateUpdate();
					co_sleep(1);
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