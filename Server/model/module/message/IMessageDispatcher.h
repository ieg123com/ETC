#pragma once
#include <memory>

namespace Model {
	class Session;
}

using namespace Model;

class IMessageDispatcher
{
public:

	virtual void Dispatch(const std::shared_ptr<Session>& session, const char* data, const size_t len) = 0;
};