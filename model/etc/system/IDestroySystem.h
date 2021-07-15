#pragma once


namespace Model
{
	class Object;

	class IDestroySystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) = 0;
	};


	template<typename T>
	class DestroySystem :
		public IDestroySystem
	{
	public:
		virtual void Run(std::shared_ptr<Object> self) override {
			Destroy(std::static_pointer_cast<T>(self));
		}

		virtual void Destroy(std::shared_ptr<T> self) = 0;
	};
}