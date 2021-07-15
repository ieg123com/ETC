#pragma once


namespace Model
{
	class IUpdateSystem
	{

	};

	template<typename T>
	class UpdateSystem :
		public IUpdateSystem
	{
	public:
		virtual void Run(T self) = 0;
	};
}