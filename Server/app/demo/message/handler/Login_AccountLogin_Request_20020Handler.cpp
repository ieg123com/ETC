#include "model/module/message.h"
#include "model/module/other/AppType.h"
#include "model/proto/DemoMsg.pb.h"
#include "model/proto/Login.pb.h"
#include "demo/Entity/PlayerEntity.h"
#include "model/module/actor/MailBoxComponent.h"


namespace Hotfix
{
	class Login_AccountLogin_Request_20020Handler : public AMRpcHandler<login::Login_AccountLogin_Request_20020, login::Login_AccountLogin_Response_20021>
	{
	public:
		virtual void Run(const std::shared_ptr<Session>& session, login::Login_AccountLogin_Request_20020& request, login::Login_AccountLogin_Response_20021& response, FMReply& reply)override
		{
			LOG_WARN("Login_AccountLogin_Request_20020Handler TypeName:{}",request.GetTypeName());

			auto player = ObjectFactory::Create<PlayerEntity>();
			player->AddComponent<MailBoxComponent>();

			auto req = std::make_shared<ActorTestRequest>();
			req->set_a(1);
			req->set_b(2);
			for (int i = 0; i < 1; ++i)
			{
				LOG_INFO("发送 Actor 消息");
				auto rpo = ActorMessageSenderComponent::Instance->Call<ActorTestResponse>(player->InstanceId(), req);
				LOG_INFO("Actor 回复消息:{}", rpo->DebugString());
			}
			


			reply();
		}
	};
	REF(Login_AccountLogin_Request_20020Handler, Message(EAppType::Login));
}