#include "MemorySplit.h"
namespace Model
{
	MemorySplit::MemorySplit()
	{
		m_pack_size = -1;
	}

	MemorySplit::~MemorySplit()
	{

	}


	void MemorySplit::AddData(const char* data, const size_t len)
	{
		__AddData(data, len);
	}

	void MemorySplit::Write(const char* data, const size_t len)
	{
		m_recv_buffer.Write(data, len);
	}


	bool MemorySplit::Unpack()
	{
		return __Unpack();
	}


	void MemorySplit::__AddData(const char* data, const size_t len)
	{
		uint16_t pack_size = len;
		m_recv_buffer.Write(&pack_size,sizeof(pack_size));
		m_recv_buffer.Write(data, len);
	}

	bool MemorySplit::__Unpack()
	{
		if (m_pack_size == -1)
		{
			uint16_t pack_size = 0;
			if (m_recv_buffer.Length() >= sizeof(pack_size))
			{
				m_recv_buffer.Read(&pack_size, sizeof(pack_size));
				m_pack_size = pack_size;
				if (m_pack_size > UINT16_MAX)
					throw std::exception("½â°üÊ±£¬pack_size > UINT16_MAX");
			}
			else {
				return false;
			}
		}

		if (m_recv_buffer.Length() >= m_pack_size)
		{
			Data.resize(m_pack_size);
			m_recv_buffer.Read((char*)Data.data(), m_pack_size);
			m_pack_size = -1;
			return true;
		}
		return false;
	}
}
