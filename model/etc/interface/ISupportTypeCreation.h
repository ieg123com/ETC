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
		virtual void BeginInit() { printf("begin init\n"); }
		virtual void EndInit() { printf("end init\n"); }
	};

}