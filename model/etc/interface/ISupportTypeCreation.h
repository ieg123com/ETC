#pragma once


namespace Model
{
	/**
	 * @brief	�̳еĶ���,��֧��ͨ�� Type ���д���
	 */
	class ISupportTypeCreation
	{
	public:
		ISupportTypeCreation(){}
		virtual void BeginInit() {}
		virtual void EndInit() {}
	};

}