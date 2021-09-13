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

	// 对象通过 ObjectFactroy 创建时，将会触发
	template<typename T,typename ...Arg>
	class AwakeSystem :
		public IAwake<Arg...>
	{
	public:

		virtual void Run(const std::shared_ptr<Object>& self, Arg...arg) override {
			Awake(std::static_pointer_cast<T>(self), arg...);
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual const TypeIndex GetCallbackType()const { return to_typeindex<void(Arg...)>(); }
		virtual void Awake(const std::shared_ptr<T>& self, Arg...arg) = 0;

	};
}