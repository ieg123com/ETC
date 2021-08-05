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

		virtual void Run(Arg...arg) = 0;
 	};


	template<typename ...Arg>
	class IObjEvent :
		public IObjEventSystem
	{
	public:
		virtual void Handle(std::shared_ptr<Object> self,Arg...arg) = 0;

	};


	template<typename T,typename ...Arg>
	class ObjEventSystem :
		public IObjEvent<Arg...>
	{
	public:
		virtual void Handle(std::shared_ptr<Object> self,Arg...arg) override {
			Run(std::static_pointer_cast<T>(self),arg...);
		}

		virtual void Run(std::shared_ptr<T> self,Arg...arg) = 0;
	};


}

