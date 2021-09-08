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

	// protobuf 协议生成代码使用
	// 用于标记告诉 MessageDispatcher 这是一条pb协议
	class ProtoMessage : public Reflection::BaseAttribute<ProtoMessage>
	{
	public:
		ProtoMessage()
		{
		}
	};

	// protobuf 协议生成代码使用
	// 用来告诉其他组件，这条请求协议的回复类型
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