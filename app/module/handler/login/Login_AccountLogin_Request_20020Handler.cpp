#include "etc/etc.h"
#include "model/module/other/AppType.h"
#include "model/proto/login.pb.h"


namespace Hotfix
{
	class Login_AccountLogin_Request_20020Handler : public RpcMessageSystem<login::Login_AccountLogin_Request_20020, login::Login_AccountLogin_Response_20021>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, login::Login_AccountLogin_Request_20020& request, login::Login_AccountLogin_Response_20021& response, std::function<void()>& reply)override
		{
			LOG_WARN("Login_AccountLogin_Request_20020Handler {}",request.DebugString());
			
			reply();
		}
	};
	REF(Login_AccountLogin_Request_20020Handler, Message(EAppType::Login));
}