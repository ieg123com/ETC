#pragma once
#include "type/type.h"
#include "interface/ISupportTypeCreation.h"

namespace Model
{
	class IEventSystem:
		public ISupportTypeCreation
	{
	public:
		virtual const Type& GetType()const = 0;

	};

	template<typename ...Arg>
	class IEvent
	{
	public:
		virtual void Run(Arg...arg) = 0;


	};


// 	template<typename T,typename ...Arg>
// 	class EventSystem
// 	{
// 	public:
// 
// 
// 	};

}

