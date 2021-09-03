#pragma once
#include "etc/etc.h"

// 信箱类型
enum class MailBoxType : uint8_t
{
	GateSession,
	MessageDispatcher,
};


// 信箱组件
class MailBoxComponent :
	public Component
{
public:
	MailBoxType	MailBoxType;

};