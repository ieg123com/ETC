#pragma once



namespace Model
{
	class Object;

	class IAwakeSystem
	{

	};

	template<typename ...Arg>
	class IAwake
	{
	public:
		virtual void Run(std::shared_ptr<Object> self, Arg ...arg) = 0;
	};

	template<typename T,typename ...Arg>
	class AwakeSystem :
		public IAwake<Arg...>,
		public IAwakeSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self, Arg...arg) override {
			Awake(std::static_pointer_cast<T>(self), arg...);
		}

		virtual void Awake(std::shared_ptr<T> self,Arg...arg) = 0;
	};
}