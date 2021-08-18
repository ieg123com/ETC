#pragma once
#include <queue>



// 循环缓存区
class CircularBuffer
{
	const size_t m_chunk_size = 8192;
	std::queue<char*> m_buffer_queue;
	std::queue<char*> m_buffer_cache;	// 缓存
	size_t m_first_index = 0;
	size_t m_last_index = m_chunk_size;
	char* m_last_buffer = nullptr;


	char* First() {
		if (m_buffer_queue.empty())
		{
			AddLast();
		}
		return m_buffer_queue.front();
	}

	char* Last() {
		if (m_buffer_queue.empty())
		{
			AddLast();
		}
		return m_last_buffer;
	}

	void AddLast() {
		char* buffer;
		if (m_buffer_cache.empty())
		{
			buffer = new char[m_chunk_size];
		}
		else {
			buffer = m_buffer_cache.front();
			m_buffer_cache.pop();
		}
		m_buffer_queue.push(buffer);
		m_last_buffer = buffer;
	}

	void RemoveFirst() {
		m_buffer_cache.push(m_buffer_queue.front());
		m_buffer_queue.pop();
	}

public:
	~CircularBuffer() {
		Clear();
		while (!m_buffer_cache.empty())
		{
			delete m_buffer_cache.front();
			m_buffer_cache.pop();
		}
	}

	size_t Length() {
		return (m_buffer_queue.empty()) ? 0 : ((m_buffer_queue.size() - 1) * m_chunk_size + m_last_index - m_first_index);
	}



	void Read(void* data, const size_t count){
		if (count > Length()) {
			throw std::exception("buffer list length < count");
		}
		size_t already_copy_count = 0;
		while (already_copy_count < count) {
			size_t n = count - already_copy_count;
			if (m_chunk_size - m_first_index > n) {
				// 可以全部拷贝
				memcpy(((char*)data + already_copy_count), First()+m_first_index, n);
				m_first_index += n;
				already_copy_count += n;
			}
			else {
				memcpy(((char*)data + already_copy_count), First() + m_first_index, m_chunk_size - m_first_index);
				already_copy_count += m_chunk_size - m_first_index;
				m_first_index = 0;
				RemoveFirst();
			}
		}
	}

	void Write(const void* data, const size_t count) {
		size_t already_copy_count = 0;
		while (already_copy_count < count) {
			if (m_last_index == m_chunk_size)
			{
				AddLast();
				m_last_index = 0;
			}

			int n = count - already_copy_count;
			if (m_chunk_size - m_last_index > n)
			{
				memcpy(m_last_buffer + m_last_index,
					((char*)data + already_copy_count), n);
				m_last_index += count - already_copy_count;
				already_copy_count += n;
			}
			else
			{
				memcpy(m_last_buffer + m_last_index,
					((char*)data + already_copy_count), 
					m_chunk_size - m_last_index);
				already_copy_count += m_chunk_size - m_last_index;
				m_last_index = m_chunk_size;
			}
		}
	}
	
	void Clear() {
		m_first_index = 0;
		m_last_index = m_chunk_size;
		m_last_buffer = nullptr;
		while (!m_buffer_queue.empty())
		{
			RemoveFirst();
		}
	}




	

};