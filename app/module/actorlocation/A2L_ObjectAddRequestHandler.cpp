#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/actorlocation/LocationComponent.h"


namespace Hotfix
{
	class A2L_ObjectAddRequestHandler : public AMActorRpcHandler<App, A2L_ObjectAddRequest, L2A_ObjectAddResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<App>& app, A2L_ObjectAddRequest& request, L2A_ObjectAddResponse& response, FMReply& reply) override
		{
			app->GetComponent<LocationComponent>()->Add(request.key(), request.instanceid());
			reply();
		}
	};
	REF(A2L_ObjectAddRequestHandler, Message(EAppType::Location));
}
