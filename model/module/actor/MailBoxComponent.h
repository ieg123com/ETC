#pragma once
#include "etc/etc.h"

// ��������
enum class MailBoxType : uint8_t
{
	GateSession,
	// �ַ���Ϣʱ���Ὣ��Ϣ������У������ֺ�˳����зַ�
	MessageDispatcher,
	// ���ᰴ���Ⱥ�˳��ַ���Ϣ
	UnorderedMessageDispatcher,
};


// �������
class MailBoxComponent :
	public Component
{
public:
	MailBoxType	MailBoxType;

};