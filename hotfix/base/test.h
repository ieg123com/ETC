#pragma once
#include "base/reflection/reflection.h"
#include "base/task/domain_task.h"

using namespace Model::Reflection;

namespace Hotfix
{
	class RefTest : public BaseAttribute<RefTest>
	{
	public:
		RefTest(const std::string& str) {
			m_str = str;
			printf("Ref %s\n", m_str.c_str());
		}

		std::string m_str;
	};



	class Test
	{
	public:

	};
	





 	



}