#include "model/module/message.h"
#include "model/demo/Entity/PlayerEntity.h"
#include "model/proto/DemoMsg.pb.h"



namespace Hotfix
{
	class ActorLocationTestRequestHandler : public AMActorLocationRpcHandler<PlayerEntity, ActorLocationTestRequest, ActorLocationTestResponse>
	{
	public:
		virtual void Run(const std::shared_ptr<PlayerEntity>& unit, ActorLocationTestRequest& request, ActorLocationTestResponse& response, FMReply& reply) override
		{
			LOG_INFO("Actor Location 收到消息: unit id: {}", unit->Id);
			response.set_sum(request.a() + request.b());
			reply();
		}
	};
	REF(ActorLocationTestRequestHandler, Message(EAppType::Map));
}