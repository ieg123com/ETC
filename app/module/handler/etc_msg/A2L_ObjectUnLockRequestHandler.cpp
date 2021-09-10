#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class A2L_ObjectUnLockRequestHandler : public AMActorRpcHandler<World, A2L_ObjectUnLockRequest, L2A_ObjectUnLockResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectUnLockRequest& request, L2A_ObjectUnLockResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(A2L_ObjectUnLockRequestHandler, Message(EAppType::Location));
}
