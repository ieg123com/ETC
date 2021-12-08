#pragma once
#include "kernel/Entity.h"
#include "module/other/ProcessType.h"
#include "module/other/AppType.h"



namespace Model
{
	class App:
		public GEntity
	{
	public:

		EAppType		AppType;
		EProcessType	ProcessType;

	private:


	};

}