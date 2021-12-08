#pragma once
#include "model/module/message.h"
#include "model/proto/DemoMsg.pb.h"
#include "model/module/actor/MailBoxComponent.h"


namespace Hotfix
{
	void TestActorLocation() {
		LOG_INFO("Location test start");
		auto player = ObjectFactory::CreateWithId<PlayerEntity>(IdGenerator::GenId());
		player->AddComponent<MailBoxComponent>();
		LocationProxyComponent::Instance->Add(player->Id, player->InstanceId());

		LOG_INFO("location: {}",LocationProxyComponent::Instance->Get(player->Id));

		auto message = std::make_shared<ActorLocationTestRequest>();
		message->set_a(10);
		message->set_b(20);
		auto response = ActorLocationSenderComponent::Instance->Call<ActorLocationTestResponse>(player->Id, message);
		LOG_INFO("location response: {}", response->ShortDebugString());
	}
}