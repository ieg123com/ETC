#pragma once
#include "etc/etc.h"

// ��������
enum class MailBoxType : uint8_t
{
	GateSession,
	MessageDispatcher,
};


// �������
class MailBoxComponent :
	public Component
{
public:
	MailBoxType	MailBoxType;

};