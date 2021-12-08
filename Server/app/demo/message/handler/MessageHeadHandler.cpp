#include "model/module/message.h"
#include "model/proto/DemoMsg.pb.h"
#include "model/module/other/AppType.h"


namespace Hotfix
{
	class MessageHeadHandler : public AMHandler<MessageHead>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, MessageHead& request) override
		{

			LOG_INFO("MessageHead ´ïµ½:{}", request.ShortDebugString());

		}
	};
	REF(MessageHeadHandler, Message(EAppType::AllServer));


}