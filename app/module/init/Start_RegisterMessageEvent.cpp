#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message/MessageDispatcherComponent.h"
#include "model/proto/etc_message.pb.h"
#include "model/proto/login.pb.h"



namespace Hotfix
{
	class Start_RegisterMessageEvent : public EventSystem<const std::shared_ptr<MessageDispatcherComponent>&>
	{
	public:
		virtual void Run(const std::shared_ptr<MessageDispatcherComponent>& dis_msg) override
		{
			// TODO: ×¢²áÏûÏ¢id
			LOG_INFO("Start register message");

			dis_msg->RegisterMessage<TestRequest>(100);
			dis_msg->RegisterMessage<TestResponse>(101);

			dis_msg->RegisterMessage<login::Login_AccountLogin_Request_20020>(20020);
			dis_msg->RegisterMessage<login::Login_AccountLogin_Response_20021>(20021);
			dis_msg->RegisterMessage<login::Login_keyLogin_Request_20024>(20024);
			dis_msg->RegisterMessage<login::Login_keyLogin_Response_20025>(20025);


			LOG_INFO("Register message complete");

		}
	};
	REF(Start_RegisterMessageEvent, Event(ESystemEventType::StartRegMessage));


}