#include "model/module/message.h"
#include "model/proto/DemoMsg.pb.h"
#include "model/module/other/AppType.h"
#include "model/demo/Entity/PlayerEntity.h"


namespace Hotfix
{
	class ActorMessageTestHandler : public AMActorHandler<PlayerEntity,ActorMessageTest>
	{
	public:
		virtual void Run(const std::shared_ptr<PlayerEntity>& player, ActorMessageTest& request) override
		{

			LOG_INFO("ActorMessageTest ´ïµ½:{}", request.ShortDebugString());

		}
	};
	REF(ActorMessageTestHandler, Message(EAppType::AllServer));


}