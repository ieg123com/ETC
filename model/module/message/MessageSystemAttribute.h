#pragma once
#include "reflection/reflection.h"



namespace Model
{
	class Message : public Reflection::BaseAttribute<Message>
	{
	public:
		Message(const int32_t app_type)
		{

		}

		int32_t		appType;
	};
}