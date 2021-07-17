#pragma once
#include <stdio.h>
#include <string>
#include "base/task/domain_task.h"
#include "test.h"

namespace Hotfix
{
	void Start()
	{
		printf("Hotfix.dll �������!\n");

		Model::DomainTask::Instance().RunAll();

		printf("TypeID %d\n", Model::GlobalData::TypeID());
	}

	void Over()
	{
		printf("Hotfix.dll �ر�!\n");

	}
}