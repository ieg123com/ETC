#include "etc/etc.h"
#include "model/proto/EtcMsg.pb.h"
#include "model/module/other/AppType.h"


namespace Hotfix
{
	class TestRequestHandler : public AMHandler<TestRequest>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, TestRequest& request) override
		{



		}
	};
	REF(TestRequestHandler, Message(EAppType::Map));


}