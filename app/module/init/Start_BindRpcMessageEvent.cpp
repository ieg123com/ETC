#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message/OpcodeTypeComponent.h"
#include "model/proto/etc_message.pb.h"
#include "model/proto/login.pb.h"

namespace Hotfix
{
	
	class Start_BindRpcMessageEvent : public EventSystem<const std::shared_ptr<OpcodeTypeComponent>&>
	{
	public:
		virtual void Run(const std::shared_ptr<OpcodeTypeComponent>& msg_bind) override
		{
			// TODO: 绑定Rpc消息
			LOG_INFO("Start bind rpc message");

			// 以在Handler里使用的消息，不需要在这里绑定
			msg_bind->BindRpcMessage<TestRequest, TestResponse>();
			msg_bind->BindRpcMessage<login::Login_AccountLogin_Request_20020, login::Login_AccountLogin_Response_20021>();
			msg_bind->BindRpcMessage<login::Login_keyLogin_Request_20024, login::Login_keyLogin_Response_20025>();


			LOG_INFO("Bind rpc message complete!");

		}
	};
	REF(Start_BindRpcMessageEvent, Event(ESystemEventType::StartBindRpcMessage));


}