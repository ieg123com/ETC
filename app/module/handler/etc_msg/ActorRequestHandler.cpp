#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"


namespace Hotfix
{
	class ActorRequestHandler : public AMActorRpcHandler<GEntity, ActorRequest, ActorResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<GEntity>& unit, ActorRequest& request, ActorResponse& response, FMReply& reply) override
		{
			reply();
		}
	};
	REF(ActorRequestHandler, Message(EAppType::AllServer));
}

