#pragma once
#include "kernel/IdGenerator.h"
#include "net/NetworkComponent.h"


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




namespace Model
{
	// ÄÚÍø×é¼þ
	class NetInnerComponent :
		public NetworkComponent
	{
	public:
		static NetInnerComponent* Instance;

		std::unordered_map<IPEndPoint, std::shared_ptr<Session>> __m_address_sessions;



		std::shared_ptr<Session> Get(const IPEndPoint& address);


		void Destroy();


	protected:
		virtual void OnConnectComplete(const std::shared_ptr<Session>& session) override;

		virtual void OnAccept(const std::shared_ptr<Session>& session) override;

		virtual void OnDisconnect(const std::shared_ptr<Session>& session) override;

	};
}
