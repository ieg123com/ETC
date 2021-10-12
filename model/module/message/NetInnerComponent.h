#pragma once
#include "etc/etc.h"
#include "net/Session.h"

struct ProcessActorId
{
	int32_t	Process;
	int64_t ActorId;
	ProcessActorId(const int64_t actor_id)
	{
		InstanceIdStruct instance_id_struct(actor_id);
		ActorId = actor_id;
		Process = instance_id_struct.process;
	}
};



class IMessageDispatcher;

namespace Model
{
	class AService;
	// 内网组件
	class NetInnerComponent :
		public GEntity
	{
	public:
		static NetInnerComponent* Instance;

		IMessageDispatcher* __MessageDispatcher;

		std::shared_ptr<AService>	__Service;


		void Destroy();


		std::shared_ptr<Session> GetOrCreate(const int64_t channel_id, const IPEndPoint& address);

		void __OnAccept(const int64_t channel_id, const IPEndPoint& address);
		void __OnRead(const int64_t channel_id, std::shared_ptr<std::vector<char>> data);
		void __OnDisconnect(const int64_t channel_id);
	};
}
