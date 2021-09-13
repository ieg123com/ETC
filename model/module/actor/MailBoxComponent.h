#pragma once
#include "etc/etc.h"

// 信箱类型
enum class MailBoxType : uint8_t
{
	GateSession,
	// 分发消息时，会将消息加入池中，按照现后顺序进行分发
	MessageDispatcher,
	// 不会按照先后顺序分发消息
	UnorderedMessageDispatcher,
};


// 信箱组件
class MailBoxComponent :
	public Component
{
public:
	MailBoxType	MailBoxType;

};