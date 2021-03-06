#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/actorlocation/LocationComponent.h"


namespace Hotfix
{
	class A2L_ObjectRemoveRequestHandler : public AMActorRpcHandler<App, A2L_ObjectRemoveRequest, L2A_ObjectRemoveResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<App>& app, A2L_ObjectRemoveRequest& request, L2A_ObjectRemoveResponse& response, FMReply& reply) override
		{
			app->GetComponent<LocationComponent>()->Remove(request.key());
			reply();
		}
	};
	REF(A2L_ObjectRemoveRequestHandler, Message(EAppType::Location));
}
