#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;
	class IUpdateSystem:
		public IEventSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) = 0;
	};

	template<typename T>
	class UpdateSystem :
		public IUpdateSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) override {
			Update(std::static_pointer_cast<T>(self));
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual const TypeIndex GetCallbackType()const { return to_typeindex<void>(); }
		virtual void Update(const std::shared_ptr<T>& self) = 0;
	};
}