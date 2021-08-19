#include "MessageDispatcherComponent.h"


namespace Model
{
	MessageDispatcherComponent* MessageDispatcherComponent::Instance = nullptr;


	class MessageDispatcherComponentLoadSystem :public LoadSystem<MessageDispatcherComponent>
	{
	public:
		virtual void Load(const std::shared_ptr<MessageDispatcherComponent>& self)override
		{
			MessageDispatcherComponent::Instance = self.get();
		}
	};
	REF(MessageDispatcherComponentLoadSystem, ObjectSystem);



}