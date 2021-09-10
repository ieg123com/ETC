#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class A2L_ObjectRemoveRequestHandler : public AMActorRpcHandler<World, A2L_ObjectRemoveRequest, L2A_ObjectRemoveResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectRemoveRequest& request, L2A_ObjectRemoveResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(A2L_ObjectRemoveRequestHandler, Message(EAppType::Location));
}
