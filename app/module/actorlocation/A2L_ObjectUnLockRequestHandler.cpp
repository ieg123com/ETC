#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/actorlocation/LocationComponent.h"


namespace Hotfix
{
	class A2L_ObjectUnLockRequestHandler : public AMActorRpcHandler<App, A2L_ObjectUnLockRequest, L2A_ObjectUnLockResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<App>& app, A2L_ObjectUnLockRequest& request, L2A_ObjectUnLockResponse& response, FMReply& reply) override
		{
			app->GetComponent<LocationComponent>()->UnLock(request.key(), request.oldinstanceid(), request.instanceid());
			reply();
		}
	};
	REF(A2L_ObjectUnLockRequestHandler, Message(EAppType::Location));
}
