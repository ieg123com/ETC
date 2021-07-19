#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;

	class ILateUpdateSystem:
		public IEventSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) = 0;
	};

	template<typename T>
	class LateUpdateSystem :
		public ILateUpdateSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self)override {
			LateUpdate(std::static_pointer_cast<T>(self));
		}
		virtual const Type& GetType()const override { return typeof(T); }
		virtual void LateUpdate(std::shared_ptr<T> self) = 0;
	};
}