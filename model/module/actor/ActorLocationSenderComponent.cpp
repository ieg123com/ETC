#include "ActorLocationSenderComponent.h"
#include "module/message/NetInnerComponent.h"
#include "module/message/OpcodeTypeComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "ActorMessageSender.h"
#include "ActorHandler.h"


ActorLocationSenderComponent* ActorLocationSenderComponent::Instance = nullptr;


void ActorLocationSenderComponent::Check()
{
	time_t out_time = Game::Time().NowServerMilliseconds() + OUTTIME_TIME;
	for (auto& item : m_request_callback)
	{
		if (item.second->m_create_time > out_time)
		{
			m_timeout_actor_message.push_back(item.first);
		}
	}

	
	for (auto& item : m_timeout_actor_message)
	{
		// 这些都是超时的消息
		auto actor_message = m_request_callback[item];
		try
		{
			auto response = ActorHandler::CreateResponseTry<IActorResponse>(actor_message->m_proto_request, ETC_ERR::ActorTimeout);
			__Run(actor_message, response);
		}
		catch (std::exception& e)
		{
			
		}
		catch (...)
		{

		}
		




	}



}


void ActorLocationSenderComponent::Send(const int64_t actor_id, const std::shared_ptr<IActorMessage>& message)
{
	__Send(actor_id, message);
}



std::shared_ptr<IActorResponse> ActorLocationSenderComponent::__Call(const int64_t actor_id, const int32_t rpc_id, const std::shared_ptr<IMessage>& message)
{
	if (actor_id == 0)
		throw std::exception(std::format("actor id is 0 : %s", message->GetTypeName().c_str()).c_str());

	auto actor_message = ActorMessageSenderPool::Instance().Fetch(actor_id, message);
	m_request_callback.emplace(rpc_id, actor_message);

	__Send(actor_id, message);

	std::shared_ptr<IActorResponse> response;

	time_t begin_time = Game::Time().NowServerMilliseconds();
	actor_message->m_proto_response >> response;
	time_t end_time = Game::Time().NowServerMilliseconds();

	return response;
}

void ActorLocationSenderComponent::__Send(const int64_t actor_id, const std::shared_ptr<IMessage>& message)
{
	// 这里通过解析 actor_id 获取进程id,再通过数据发送到指定进程中去
	// 执行时会出意外，不过可以当超时处理。所以没有对失败情况进行处理
	if (actor_id == 0)
		throw std::exception(std::format("actor id is 0 : %s", message->GetTypeName().c_str()).c_str());

	int32_t process = ProcessActorId(actor_id).Process;
	if (auto process_config = StartConfigComponent::Instance->Get(process))
	{
		if (auto session = NetInnerComponent::Instance->Get(process_config->InnerAddress))
		{
			session->Send(actor_id, message.get());
		}
	}
}

void ActorLocationSenderComponent::__Run(const std::shared_ptr<ActorMessageSender>& actor_message,const std::shared_ptr<IActorResponse>& response)
{

}
