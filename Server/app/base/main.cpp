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

			LOG_INFO("》》》》》》启动成功");
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
					LOG_ERROR("更新时出错 {}", e.what());
				}
				catch (...)
				{
					LOG_ERROR("更新时发生未知错误");
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
			LOG_ERROR("启动服务时发生位置错误，请检查配置是否正确！");
		}
	


	}

	};


	co_sched.Start();
	return 0;
}