#pragma once
#include "other/container/CircularBuffer.h"
#include <memory>
#include <string>



namespace Model
{
	/** @brief 内存财富 */
	class MemorySplit
	{

	public:
		MemorySplit();
		~MemorySplit();


		// 拆包后的数据
		std::string Data;

		// 添加要分割的数据
		void AddData(const char* data, const size_t len);

		bool Unpack();


	private:

		void __AddData(const char* data, const size_t len);
		/**
		 * @brief	开始拆包
		 */
		bool __Unpack();


	private:

		CircularBuffer m_recv_buffer;

		size_t	m_pack_size;

	};

}
