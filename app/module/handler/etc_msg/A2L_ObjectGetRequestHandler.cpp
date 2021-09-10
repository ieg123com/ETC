#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class A2L_ObjectGetRequestHandler : public AMActorRpcHandler<World, A2L_ObjectGetRequest, L2A_ObjectGetResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<World>& world, A2L_ObjectGetRequest& request, L2A_ObjectGetResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(A2L_ObjectGetRequestHandler, Message(EAppType::Location));
}
