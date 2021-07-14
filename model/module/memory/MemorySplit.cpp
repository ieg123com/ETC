#include "MemorySplit.h"
namespace Model
{
	MemorySplit::MemorySplit()
	{
		m_list_start = MemoryLoop::Instance().Fetch<SplitData>();
		m_list_over = m_list_start;
	}

	MemorySplit::~MemorySplit()
	{
		while (m_list_start != nullptr)
		{
			MemoryLoop::Instance().Recycle(m_list_start);
			m_list_start = m_list_start->next;
		}
		m_list_over = m_list_start;
	}


	void MemorySplit::AddData(const char* data, const size_t len)
	{
		__AddData(data, len);
	}

	bool MemorySplit::Unpack()
	{
		return __Unpack();
	}


	void MemorySplit::__AddData(const char* data, const size_t len)
	{
		size_t left_len = len;
		const char* data_pos = data;
		while (left_len != 0)
		{
			if (m_list_over->leftsize() == 0)
			{
				// 这块空间满了,重新开辟一块空间
				m_list_over->next = MemoryLoop::Instance().Fetch<SplitData>();
				m_list_over = m_list_over->next;
			}
			size_t size = m_list_over->push_back(data_pos, left_len);

			data_pos += left_len - size;
			left_len = size;
		}
	}

	bool MemorySplit::__Unpack()
	{
		uint16_t pack_size = 0;
		size_t sum_size = m_list_start->sizesum();
		if (sum_size < sizeof(pack_size))
		{
			return false;
		}
		sum_size -= sizeof(pack_size);
		m_list_start->front_from_allpack(&pack_size, sizeof(pack_size));
		printf("pack size %d\n", pack_size);
		if (sum_size < pack_size)
		{
			return false;
		}
		m_list_start->pop_from_allpack(sizeof(pack_size));

		Data = std::make_shared<std::string>();
		Data->resize((size_t)pack_size);

		m_list_start->front_pop_from_allpack((void*)Data->data(), (size_t)pack_size);
		while (m_list_start->next != nullptr)
		{
			if (m_list_start->size() == 0)
			{
				auto child = m_list_start;
				m_list_start = m_list_start->next;
				MemoryLoop::Instance().Recycle(child);
			}
			else {
				break;
			}
		}
		return true;
	}
}
