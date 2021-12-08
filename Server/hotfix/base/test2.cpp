#pragma once
#include "test.h"
#include "etc.h"

using namespace Model;

namespace Hotfix
{
	class TestB :public Model::ISupportTypeCreation
	{
	public:

	};

	REF(TestB, RefTest("789"))
	//REF(TestB, ObjectSystem)



}

