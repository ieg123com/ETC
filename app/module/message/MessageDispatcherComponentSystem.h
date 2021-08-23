#include "model/module/message/MessageDispatcherComponent.h"
#include "model/module/other/SystemEventType.h"

using namespace Model;


namespace Hotfix
{

	class MessageDispatcherComponentAwakeSystem :public AwakeSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Awake(const std::shared_ptr<MessageDispatcherComponent>& self) override
		{
			LOG_INFO("MessageDispatcherComponent Awake");
			self->Awake();
		}
	};
	REF(MessageDispatcherComponentAwakeSystem, ObjectSystem);

	class MessageDispatcherComponentLoadSystem :public LoadSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<MessageDispatcherComponent>& self)override
		{
			LOG_INFO("MessageDispatcherComponent Load");
			MessageDispatcherComponent::Instance = self.get();
			Game::Event().Run(ESystemEventType::StartRegMessage);

		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);

}


