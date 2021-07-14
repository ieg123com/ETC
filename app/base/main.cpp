#include <stdio.h>
#include <iostream>
#include "helper/hotfix/HotfixHelper.h"
#include "base/init.h"
#include "coroutine.h"


int main(int argc,char* argv[])
{
	go []{
		Model::Init();
		Model::Hotfix hotfix;
		try
		{
			hotfix.Load("hotfix.dll");
			hotfix.Init(Model::GetGlobalVar());
		}
		catch (std::exception& e)
		{
			printf("加载热更文件出错 %s\n", e.what());
		}
		printf("");
	};


	co_sched.Start();
	return 0;
}