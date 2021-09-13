#pragma once
#include "IEventSystem.h"


namespace Model
{
	class Object;
	class ILoadSystem :
		public IEventSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) = 0;
	};

	// 对象通过 ObjectFactroy 创建时，会紧随 AwakeSystem 后面触发
	// 当模组被载入时，也会触发
	template<typename T>
	class LoadSystem :
		public ILoadSystem
	{
	public:
		virtual void Run(const std::shared_ptr<Object>& self) override {
			Load(std::static_pointer_cast<T>(self));
		}

		virtual const Type GetType()const override { return typeof(T); }
		virtual const TypeIndex GetCallbackType()const { return to_typeindex<void()>(); }
		virtual void Load(const std::shared_ptr<T>& self) = 0;
	};
}