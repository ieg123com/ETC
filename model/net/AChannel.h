#pragma once
#include "net/IPEndPoint.h"


namespace Model
{
	class AChannel
	{
	public:
		int64_t	Id;

		IPEndPoint RemoteAddress;

		AChannel(int64_t id):Id(id){}

		virtual bool IsDisposed() {
			return (Id == 0);
		}

		virtual void Dispose() {
			Id = 0;
		}
	};
}