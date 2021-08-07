#pragma once
#include "type/type.h"
#include "interface/ISupportTypeCreation.h"


namespace Model
{
	class Object;

	class IEventSystem:
		public ISupportTypeCreation
	{
	public:
		virtual const Type GetType()const = 0;
		virtual const std::type_info* GetArgType()const = 0;

	};

	class IObjEventSystem :
		public IEventSystem
	{
	public:

	};

	template<typename ...Arg>
	class IEvent:
		public IEventSystem
	{
	public:
		virtual void Handle(Arg...arg) = 0;

	};


 	template<typename ...Arg>
 	class EventSystem:
		public IEvent<Arg...>
 	{
 	public:
		virtual void Handle(Arg...arg) override {
			Run(arg...);
		}

		virtual const Type GetType()const { return typeof(Object); }
		virtual const std::type_info* GetArgType()const { return &typeid(void(Arg...)); }
		virtual void Run(Arg...arg) = 0;
 	};


	template<typename ...Arg>
	class IObjEvent :
		public IObjEventSystem
	{
	public:
		virtual void Handle(const std::shared_ptr<Object>& self,Arg...arg) = 0;

	};


	template<typename T,typename ...Arg>
	class ObjEventSystem :
		public IObjEvent<Arg...>
	{
	public:
		virtual void Handle(const std::shared_ptr<Object>& self,Arg...arg) override {
			Run(std::static_pointer_cast<T>(self),arg...);
		}

		virtual const Type GetType()const { return typeof(T); }
		virtual const std::type_info* GetArgType()const { return &typeid(void(Arg...)); }
		virtual void Run(const std::shared_ptr<T>& self, Arg...arg) = 0;
	};


}

