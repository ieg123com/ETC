#pragma once
#include "type/type.h"

namespace Model
{
	/**
	 * @brief	�̳еĶ���,��֧��ͨ�� Type ���д���
	 */
	class ISupportTypeCreation
	{
		friend class TypeFactory;
	public:
		ISupportTypeCreation(){}
		virtual void BeginInit() {}
		virtual void EndInit() {}


	private:
		Type m_self_type;
		
	};

}