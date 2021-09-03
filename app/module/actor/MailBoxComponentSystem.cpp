#include "model/module/actor/MailBoxComponent.h"



class MailBoxCompoentAwakeSystem : public AwakeSystem<MailBoxComponent>
{
public:
	virtual void Awake(const std::shared_ptr<MailBoxComponent>& self)override
	{
		self->MailBoxType = MailBoxType::MessageDispatcher;
	}
};
REF(MailBoxCompoentAwakeSystem, ObjectSystem);

class MailBoxCompoentAwakeSystem1 : public AwakeSystem<MailBoxComponent,MailBoxType>
{
public:
	virtual void Awake(const std::shared_ptr<MailBoxComponent>& self, MailBoxType type)override
	{
		self->MailBoxType = type;
	}
};
REF(MailBoxCompoentAwakeSystem1, ObjectSystem);