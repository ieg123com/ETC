#pragma once
#include "IEventSystem.h"

namespace Model
{
	class Object;

	class IDestroySystem:
		public IEventSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) = 0;
	};


	template<typename T>
	class DestroySystem :
		public IDestroySystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) override {
			Destroy(std::static_pointer_cast<T>(self));
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual void Destroy(const std::shared_ptr<T>& self) = 0;
	};
}