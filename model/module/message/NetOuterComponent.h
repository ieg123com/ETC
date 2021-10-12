#pragma once
#include "etc/etc.h"
#include "net/IPEndPoint.h"
#include "net/Session.h"

class IMessageDispatcher;

namespace Model
{
	class AService;

	// 外网组件
	class NetOuterComponent :
		public GEntity
	{
	public:

		IMessageDispatcher* __MessageDispatcher;

		std::shared_ptr<AService>	__Service;

		void Destroy();


		void __OnAccept(const int64_t channel_id, const IPEndPoint& address);
		void __OnRead(const int64_t channel_id, std::shared_ptr<std::vector<char>> data);
		void __OnDisconnect(const int64_t channel_id);


	};
}
