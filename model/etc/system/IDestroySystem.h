#pragma once


namespace Model
{
	class IDestroySystem 
	{

	};

	template<typename T>
	class DestroySystem :
		public IDestroySystem
	{
	public:
		virtual void Run(T self) = 0;
	};
}