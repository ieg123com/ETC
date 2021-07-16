#pragma once


namespace Model
{
	class Object;
	class IUpdateSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) = 0;

	};

	template<typename T>
	class UpdateSystem :
		public IUpdateSystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) override {
			Update(std::static_pointer_cast<T>(self));
		}

		virtual void Update(std::shared_ptr<T> self) = 0;
	};
}