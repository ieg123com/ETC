#include "model/module/message.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/demo/Entity/PlayerEntity.h"


namespace Hotfix
{
	class ActorTestRequestHandler : public AMActorRpcHandler<PlayerEntity, ActorTestRequest, ActorTestResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<PlayerEntity>& unit, ActorTestRequest& request, ActorTestResponse& response, FMReply& reply) override
		{

			LOG_INFO("====>Actor 消息达到!");
			int32_t a = request.a();
			int32_t b = request.b();

			response.set_sum(a + b);

			reply();
		}
	};
	REF(ActorTestRequestHandler, Message(EAppType::AllServer));
}
