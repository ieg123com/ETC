#pragma once



namespace Model
{
	class IAwakeSystem
	{

	};

	template<typename T,typename ...Arg>
	class AwakeSystem :
		public IAwakeSystem
	{
	public:
		virtual void Run(T self, Arg...arg) = 0;
	};
}