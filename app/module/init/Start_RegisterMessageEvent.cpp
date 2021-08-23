#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message/MessageDispatcherComponent.h"
#include "model/proto/etc_message.pb.h"


using namespace Model;

namespace Hotfix
{
	class Start_RegisterMessageEvent : public EventSystem<const std::shared_ptr<MessageDispatcherComponent>&>
	{
	public:
		virtual void Run(const std::shared_ptr<MessageDispatcherComponent>& dis_msg) override
		{

			LOG_INFO("Register message event");

			dis_msg->RegisterMessage<TestRequest>(100, EAppType::Map | EAppType::Chat);
			dis_msg->RegisterMessage<TestResponse>(100, EAppType::Map | EAppType::Chat);



		}
	};
	REF(Start_RegisterMessageEvent, Event(ESystemEventType::StartRegMessage));


}