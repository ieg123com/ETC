#pragma once
#include <memory>
#include <string>
#include <vector>

class CircularBuffer;

namespace Model
{

	class PacketParser
	{
	public:
		PacketParser(const std::shared_ptr<CircularBuffer>& buffer);
		~PacketParser();


		// ����������
		std::shared_ptr<std::vector<char>> Data;

		/**
		 * @brief	��ʼ���
		 */
		bool Unpack();



	private:

		std::shared_ptr<CircularBuffer> m_recv_buffer;

		size_t	m_pack_size;

	};
}