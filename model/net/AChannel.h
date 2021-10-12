#pragma once
#include "net/IPEndPoint.h"
#include <memory>


namespace Model
{
	enum class EChannelType
	{
		Connect,
		Accept,
	};

	class AChannel :
		public std::enable_shared_from_this<AService>
	{
	public:

		template<typename T>
		std::shared_ptr<T> Get() {
			return std::static_pointer_cast<T>(shared_from_this());
		}


		EChannelType	ChannelType;

		int64_t	Id;

		IPEndPoint RemoteAddress;

		virtual bool IsDisposed() const = 0;

		virtual void Dispose() = 0;
	};
}
