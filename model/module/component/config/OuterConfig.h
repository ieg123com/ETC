#pragma once
#include "etc/etc.h"
#include "net/NetDefines.h"


namespace Model
{
	// ÍâÍøÅäÖÃ
	class OuterConfig :
		public Component
	{
	public:
		IPEndPoint Address;

	};
}