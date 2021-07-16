#pragma once


namespace Model
{
	class IEventSystem
	{

	};

	template<typename ...Arg>
	class IEvent
	{
	public:
		virtual void Run() = 0;


	};


	template<typename T,typename ...Arg>
	class EventSystem
	{
	public:


	};

}

