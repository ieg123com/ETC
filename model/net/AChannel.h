#pragma once
#include "net/IPEndPoint.h"


namespace Model
{
	enum class EChannelType
	{
		Connect,
		Accept,
	};

	class AChannel
	{
	public:
		EChannelType	ChannelType;

		int64_t	Id;

		IPEndPoint RemoteAddress;

		virtual bool IsDisposed() const = 0;

		virtual void Dispose() = 0;
	};
}