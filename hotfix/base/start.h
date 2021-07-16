#pragma once
#include <stdio.h>
#include <string>
#include "base/task/domain_task.h"
#include "test.h"

namespace Hotfix
{
	void Start()
	{
		printf("Hotfix.dll 加载完成!\n");

		Model::DomainTask::Instance().RunAll();


	}

	void Over()
	{
		printf("Hotfix.dll 关闭!\n");

	}
}