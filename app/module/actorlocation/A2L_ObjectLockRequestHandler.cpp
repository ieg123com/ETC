#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/actorlocation/LocationComponent.h"


namespace Hotfix
{
	class A2L_ObjectLockRequestHandler : public AMActorRpcHandler<World, A2L_ObjectLockRequest, L2A_ObjectLockResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectLockRequest& request, L2A_ObjectLockResponse& response, FMReply& reply) override
		{
			world->GetComponent<LocationComponent>()->Lock(request.key(), request.instanceid(), request.time());
			reply();
		}
	};
	REF(A2L_ObjectLockRequestHandler, Message(EAppType::Location));
}
