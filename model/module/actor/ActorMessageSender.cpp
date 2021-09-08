#include "ActorMessageSender.h"


void ActorMessageSender::SetException(std::exception& e)
{
	HasException = true;
	Exception = std::move(e);
}