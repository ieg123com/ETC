#pragma once


namespace Model
{
	/**
	 * @brief	继承的对象,将支持通过 Type 进行创建
	 */
	class ISupportTypeCreation
	{
	public:
		ISupportTypeCreation(){}
		virtual void BeginInit() {}
		virtual void EndInit() {}
	};

}