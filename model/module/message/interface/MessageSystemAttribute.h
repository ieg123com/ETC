#pragma once
#include "reflection/reflection.h"



namespace Model
{
	class Message : public Reflection::BaseAttribute<Message>
	{
	public:
		Message(const int32_t app_type)
		{
			appType = app_type;
		}

		int32_t		appType;
	};

	// protobuf Э�����ɴ���ʹ��
	// ���ڱ�Ǹ��� MessageDispatcher ����һ��pbЭ��
	class ProtoMessage : public Reflection::BaseAttribute<ProtoMessage>
	{
	public:
		ProtoMessage()
		{
		}
	};

	// protobuf Э�����ɴ���ʹ��
	// �������������������������Э��Ļظ�����
	class ProtoResponseMessage : public Reflection::BaseAttribute<ProtoMessage>
	{
	public:
		ProtoResponseMessage(const Type& tp)
		{
			ResponseMessageType = tp;
		}

		Type ResponseMessageType;
	};
}