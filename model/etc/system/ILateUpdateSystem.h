#pragma once


namespace Model
{
	class ILateUpdateSystem
	{

	};

	template<typename T>
	class LateUpdateSystem :
		public ILateUpdateSystem
	{
	public:
		virtual void Run(T self) = 0;
	};
}