#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class A2L_ObjectAddRequestHandler : public AMActorRpcHandler<World, A2L_ObjectAddRequest, L2A_ObjectAddResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectAddRequest& request, L2A_ObjectAddResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(A2L_ObjectAddRequestHandler, Message(EAppType::Location));
}
