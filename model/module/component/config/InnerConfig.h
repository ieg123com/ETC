#pragma once
#include "etc/etc.h"
#include "net/NetDefines.h"


namespace Model
{
	// ��������
	class InnerConfig :
		public Component
	{
	public:
		IPEndPoint Address;

	};
}