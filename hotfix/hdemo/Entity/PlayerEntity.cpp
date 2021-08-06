#pragma once
#include "demo/Entity/PlayerEntity.h"

using namespace Model;

namespace Hotfix
{
	class PlayerEntityAwakeSystem : public AwakeSystem<PlayerEntity>
	{
	public:
		virtual void Awake(const std::shared_ptr<PlayerEntity>& self) override
		{
			LOG_INFO("PlayerEntity Awake");



		}
	};
	REF(PlayerEntityAwakeSystem, ObjectSystem);

	class PlayerEntityLoadSystem : public LoadSystem<PlayerEntity>
	{
	public:
		virtual void Load(const std::shared_ptr<PlayerEntity>& self) override
		{
			LOG_INFO("PlayerEntity Load");

			Game::Event().RegisterObjectEvent(self, self, "test");
		}
	};
	REF(PlayerEntityLoadSystem, ObjectSystem);


	class PlayerEntityDestroySystem : public DestroySystem<PlayerEntity>
	{
	public:
		virtual void Destroy(const std::shared_ptr<PlayerEntity>& self) override
		{
			LOG_INFO("PlayerEntity Destroy");
			Game::Event().RemoveObjectEvent(self, self, "test");


		}
	};
	REF(PlayerEntityDestroySystem, ObjectSystem);


	class TestEvent : public EventSystem<const std::string&>
	{
	public:
		virtual void Run(const std::string& str) override
		{
			LOG_INFO("Test Event {}",str);
		}
	};
	REF(TestEvent, Event("test"));

	class TestObjEvent : public ObjEventSystem<PlayerEntity,const std::string&>
	{
	public:
		virtual void Run(const std::shared_ptr<PlayerEntity>& self,const std::string& str) override
		{
			LOG_INFO("Test ObjEvent [{}] {}", self->Uuid, str);
		}
	};
	REF(TestObjEvent, ObjEvent("test"));
}

