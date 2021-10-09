#pragma once
#include "net/IPEndPoint.h"
#include <functional>

namespace Model
{
	class AService
	{
	public:


		virtual bool IsDisposed() = 0;
		virtual void Update() = 0;
		virtual void Remove(const int64_t channel_id) = 0;
		virtual void Send(const int64_t channel_id, const char* data, const size_t len) = 0;
		virtual void Dispose() = 0;

		
		std::function<void(const long, const IPEndPoint&)>	AcceptCallback;
		std::function<void(const long, std::shared_ptr<std::string>)>	ReadCallback;
		std::function<void(const long, const int)>	ErrorCallback;


	};
}