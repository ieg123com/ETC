#pragma once
#include "etc/etc.h"
#include "net/NetDefines.h"


namespace Model
{
	// ��������
	class OuterConfig :
		public Component
	{
	public:
		IPEndPoint Address;

	};
}