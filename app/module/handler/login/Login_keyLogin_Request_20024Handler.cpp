#include "etc/etc.h"
#include "model/module/other/AppType.h"
#include "model/proto/login.pb.h"


namespace Hotfix
{
	class Login_keyLogin_Request_20024Handler : public MRpcHandler<login::Login_keyLogin_Request_20024, login::Login_keyLogin_Response_20025>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, login::Login_keyLogin_Request_20024& request, login::Login_keyLogin_Response_20025& response, std::function<void()>& reply)override
		{
			LOG_WARN("Login_keyLogin_Request_20024Handler");
		}
	};
	REF(Login_keyLogin_Request_20024Handler, Message(EAppType::Gate));

}