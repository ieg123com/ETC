#include "etc/etc.h"
#include "model/proto/etc_msg.pb.h"


namespace Hotfix
{
	class ActorRequestHandler : public MActorRpcHandler<GEntity, ActorRequest, ActorResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<GEntity>& unit, ActorRequest& request, ActorResponse& response) override
		{

		}
	};
	REF(ActorRequestHandler, Message(EAppType::AllServer));
}

