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

	class ProtoMessage : public Reflection::BaseAttribute<ProtoMessage>
	{
	public:
		ProtoMessage()
		{
		}
	};

	class ProtoResponseMessage : public Reflection::BaseAttribute<ProtoMessage>
	{
	public:
		ProtoResponseMessage(const Type& tp)
		{
			MessageType = tp;
		}

		Type MessageType;
	};
}