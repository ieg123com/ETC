#include "etc/etc.h"
#include "model/proto/etc_msg.pb.h"
#include "model/module/other/AppType.h"


namespace Hotfix
{
	class TestRequestHandler : public MessageHandler<TestRequest>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, TestRequest& request) override
		{



		}
	};
	REF(TestRequestHandler, Message(EAppType::Map));


}