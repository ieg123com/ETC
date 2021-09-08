#include "ActorMessageSenderComponent.h"
#include "module/message/NetInnerComponent.h"
#include "module/message/OpcodeTypeComponent.h"
#include "module/component/StartConfigComponent.h"
#include "module/component/config/StartConfig.h"
#include "timer/TimerComponent.h"
#include "ActorMessageSender.h"
#include "ActorHandler.h"

ActorMessageSenderComponent* ActorMessageSenderComponent::Instance = nullptr;


void ActorMessageSenderComponent::Awake()
{
	auto self = Get<ActorMessageSenderComponent>();
	m_rpc_id = 0;
	m_timeout_check_timer = TimerComponent::Instance->RegisterRepeatedTimer(1000, [=] {self->Check(); });
}

void ActorMessageSenderComponent::Destory()
{
	TimerComponent::Instance->RemoveTimer(m_timeout_check_timer);
}


void ActorMessageSenderComponent::Check()
{
	time_t out_time = Game::Time().NowServerMilliseconds() - OUTTIME_TIME;
	for (auto& item : m_request_callback)
	{
		if (item.second->CreateTime < out_time)
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
			auto response = ActorHandler::CreateResponseTry<IActorResponse>(actor_message->ProtoRequest, ETC_ERR::ActorTimeout);
			m_request_callback.erase(item);
			__Run(actor_message, response);
		}
		catch (std::exception& e)
		{
			LOG_ERROR("Actor error: 超时后执行回调，发生错误!({})",e.what());
		}
		catch (...)
		{
			LOG_ERROR("Actor error: 超时后执行回调，发生错误!(未知错误)");
		}
	}

	m_timeout_actor_message.clear();

}


void ActorMessageSenderComponent::Send(const int64_t actor_id, const std::shared_ptr<IActorMessage>& message)
{
	__Send(actor_id, message);
}

void ActorMessageSenderComponent::RunMessage(const int64_t actor_id, const std::shared_ptr<IActorResponse>& response)
{
	auto found = m_request_callback.find(response->GetRpcId());
	if (found == m_request_callback.end())
	{
		return;
	}
	auto request_callback = found->second;
	m_request_callback.erase(response->GetRpcId());
	__Run(request_callback, response);
}


std::shared_ptr<IActorResponse> ActorMessageSenderComponent::__Call(const int64_t actor_id, const int32_t rpc_id, const std::shared_ptr<IMessage>& message)
{
	if (actor_id == 0)
		throw std::exception(std::format("actor id is 0 : %s", message->GetTypeName().c_str()).c_str());

	auto actor_message = ActorMessageSenderPool::Instance().Fetch(actor_id, message);
	m_request_callback.emplace(rpc_id, actor_message);

	__Send(actor_id, message);

	std::shared_ptr<IActorResponse> response;

	time_t begin_time = Game::Time().NowServerMilliseconds();
	actor_message->ProtoResponse >> response;

	if (actor_message->HasException)
	{
		// 在Rpc调用期间发生了异常
		// 将在这里抛出
		throw actor_message->Exception;
	}

	time_t end_time = Game::Time().NowServerMilliseconds();

	//if (end_time - begin_time > 200)
	{
		LOG_WARN("Actor消息回复时间太久了，end_time - begin_time = {} > 200，message type:{}", end_time - begin_time,message->GetTypeName());
	}

	return response;
}

void ActorMessageSenderComponent::__Send(const int64_t actor_id, const std::shared_ptr<IMessage>& message)
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

void ActorMessageSenderComponent::__Run(const std::shared_ptr<ActorMessageSender>& actor_message, const std::shared_ptr<IActorResponse>& response)
{
	if (response->GetError() == (int32_t)ETC_ERR::ActorTimeout)
	{
		actor_message->SetException(
			std::exception(
				std::format(
					"Rpc error: Actor超时(%d:%s), request type:%s, response type:%s", 
					response->GetError(),
					response->GetMessage().c_str(),
					actor_message->ProtoRequest->GetType().full_name(),
					response->GetType().full_name()).c_str()));
	}
	if (actor_message->HasException && IsRpcNeedThrowException((ETC_ERR)response->GetError()))
	{
		actor_message->SetException(std::exception(
			std::format(
				"Rpc error: Actor发生错误(%d:%s), request type:%s, response type:%s",
				response->GetError(),
				response->GetMessage().c_str(),
				actor_message->ProtoRequest->GetType().full_name(),
				response->GetType().full_name()).c_str()));
	}

	actor_message->ProtoResponse << response;
}



