#include "etc/etc.h"
#include "model/module/other/SystemEventType.h"
#include "model/module/message/MessageDispatcherComponent.h"
#include "model/proto/etc_msg.pb.h"
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



			LOG_INFO("Register message complete");

		}
	};
	REF(Start_RegisterMessageEvent, Event(ESystemEventType::StartRegMessage));


}