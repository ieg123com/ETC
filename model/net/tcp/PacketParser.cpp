#include "PacketParser.h"
#include "module/memory/Loop.h"
#include "other/container/CircularBuffer.h"


namespace Model
{


	PacketParser::PacketParser(const std::shared_ptr<CircularBuffer>& buffer)
	{
		m_pack_size = -1;
		m_recv_buffer = buffer;
	}

	PacketParser::~PacketParser()
	{

	}

	bool PacketParser::Unpack()
	{
		if (m_pack_size == -1)
		{
			uint16_t pack_size = 0;
			if (m_recv_buffer->Length() >= sizeof(pack_size))
			{
				m_recv_buffer->Read(&pack_size, sizeof(pack_size));
				m_pack_size = pack_size;
				if (m_pack_size > UINT16_MAX)
					throw std::exception("½â°üÊ±£¬pack_size > UINT16_MAX");
			}
			else {
				return false;
			}
		}

		if (m_recv_buffer->Length() >= m_pack_size)
		{
			Data = Loop<std::string>::Instance().Fetch();
			Data->resize(m_pack_size);
			m_recv_buffer->Read((char*)Data->data(), m_pack_size);
			m_pack_size = -1;
			return true;
		}
		return false;
	}

}