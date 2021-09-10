#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class A2L_ObjectLockRequestHandler : public AMActorRpcHandler<World, A2L_ObjectLockRequest, L2A_ObjectLockResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectLockRequest& request, L2A_ObjectLockResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(A2L_ObjectLockRequestHandler, Message(EAppType::Location));
}
