#pragma once
#include "other/container/CircularBuffer.h"
#include <memory>
#include <string>



namespace Model
{
	/** @brief �ڴ�Ƹ� */
	class MemorySplit
	{

	public:
		MemorySplit();
		~MemorySplit();


		// ����������
		std::string Data;

		// ���Ҫ�ָ������
		void AddData(const char* data, const size_t len);

		bool Unpack();


	private:

		void __AddData(const char* data, const size_t len);
		/**
		 * @brief	��ʼ���
		 */
		bool __Unpack();


	private:

		CircularBuffer m_recv_buffer;

		size_t	m_pack_size;

	};

}
