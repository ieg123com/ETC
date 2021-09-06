#include "ActorMessageSender.h"


bool ActorMessageSender::Send(const int64_t actor_id, IActorMessage* message)
{
	__Call(actor_id,)

}


std::shared_ptr<IActorResponse> ActorMessageSender::__Call(const int64_t actor_id, IActorRequest* request)
{




}