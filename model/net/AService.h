#pragma once
#include "net/IPEndPoint.h"


namespace Model
{
	class AService
	{
	public:


		virtual bool IsDisposed() = 0;
		virtual void Update() = 0;
		virtual void Remove(const int channel_id) = 0;
		virtual void Send(const int channel_id, const char* data, const size_t len) = 0;
		virtual void Dispose() = 0;
	};
}