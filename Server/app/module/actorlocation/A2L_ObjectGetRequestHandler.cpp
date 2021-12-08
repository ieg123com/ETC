#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/actorlocation/LocationComponent.h"


namespace Hotfix
{
	class A2L_ObjectGetRequestHandler : public AMActorRpcHandler<App, A2L_ObjectGetRequest, L2A_ObjectGetResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<App>& app, A2L_ObjectGetRequest& request, L2A_ObjectGetResponse& response, FMReply& reply) override
		{
			response.set_instanceid(app->GetComponent<LocationComponent>()->Get(request.key()));
			reply();
		}
	};
	REF(A2L_ObjectGetRequestHandler, Message(EAppType::Location));
}
