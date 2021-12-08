#include "model/module/message.h"
#include "model/module/other/AppType.h"
#include "model/proto/login.pb.h"


namespace Hotfix
{
	class Login_keyLogin_Request_20024Handler : public AMRpcHandler<login::Login_keyLogin_Request_20024, login::Login_keyLogin_Response_20025>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, login::Login_keyLogin_Request_20024& request, login::Login_keyLogin_Response_20025& response, FMReply& reply)override
		{
			LOG_WARN("Login_keyLogin_Request_20024Handler");
		}
	};
	REF(Login_keyLogin_Request_20024Handler, Message(EAppType::Gate));

}