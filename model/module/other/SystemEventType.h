#pragma once
#include "EventType.h"


namespace Model
{
	// �¼�ϵͳ�¼�����
	enum ESystemEventType
	{
		BEGIN	= EEventType::SYSTEM,
		StartRegMessage,		// ��ʼע���¼�
		StartBindRpcMessage,	// ��ʼ��Rpc��Ϣ

	};

}
