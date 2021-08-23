#include "etc/etc.h"
#include "model/proto/etc_message.pb.h"

using namespace Model;

namespace Hotfix
{
	class TestRequestHandler : public MessageSystem<TestRequest>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, TestRequest& request) override
		{



		}
	};
	REF(TestRequestHandler, Message);


}