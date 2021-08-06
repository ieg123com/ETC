#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;

	class IAwakeSystem:
		public IEventSystem
	{
	public:
	};

	template<typename ...Arg>
	class IAwake:
		public IAwakeSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self, Arg ...arg) = 0;
	};

	template<typename T,typename ...Arg>
	class AwakeSystem :
		public IAwake<Arg...>
	{
	public:

		virtual void Run(const std::shared_ptr<Object>& self, Arg...arg) override {
			Awake(std::static_pointer_cast<T>(self), arg...);
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual void Awake(const std::shared_ptr<T>& self, Arg...arg) = 0;

	};
}