#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;
	class IStartSystem:
		public IEventSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) = 0;
	};

	template<typename T>
	class StartSystem :
		public IStartSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) override {
			Start(std::static_pointer_cast<T>(self));
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual const std::type_info* GetCallbackType()const { return &typeid(void()); }
		virtual void Start(const std::shared_ptr<T>& self) = 0;
	};
}