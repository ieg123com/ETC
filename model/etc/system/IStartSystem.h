#pragma once


namespace Model
{
	class Object;
	class IStartSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) = 0;
	};

	template<typename T>
	class StartSystem :
		public IStartSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) override {
			Start(std::static_pointer_cast<T>(self));
		}

		virtual void Start(std::shared_ptr<T> self) = 0;
	};
}