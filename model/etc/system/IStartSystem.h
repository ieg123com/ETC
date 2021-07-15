#pragma once


namespace Model
{
	class IStartSystem
	{

	};

	template<typename T>
	class StartSystem :
		public IStartSystem
	{
	public:
		virtual void Run(T self) = 0;
	};
}