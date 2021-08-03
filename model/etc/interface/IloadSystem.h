#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;
	class ILoadSystem :
		public IEventSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) = 0;
	};

	template<typename T>
	class LoadSystem :
		public ILoadSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) override {
			Start(std::static_pointer_cast<T>(self));
		}

		virtual const Type& GetType()const override { return typeof(T); }
		virtual void Start(std::shared_ptr<T> self) = 0;
	};
}