#pragma once
#include <memory>
#include <string>

class CircularBuffer;

namespace Model
{

	class PacketParser
	{
	public:
		PacketParser(const std::shared_ptr<CircularBuffer>& buffer);
		~PacketParser();


		// 拆包后的数据
		std::shared_ptr<std::string> Data;

		/**
		 * @brief	开始拆包
		 */
		bool Unpack();



	private:

		std::shared_ptr<CircularBuffer> m_recv_buffer;

		size_t	m_pack_size;

	};
}