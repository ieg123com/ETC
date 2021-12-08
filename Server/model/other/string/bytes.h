#pragma once
#include <iostream>
#include <string>

class Bytes
{
	friend std::ostream& operator<<(std::ostream&, Bytes&);
public:
	Bytes(const void* bytes, const size_t len) {
		m_bytes = (unsigned char*)bytes;
		m_len = len;
	}

	std::string ToString() {
		std::string reply;
		reply = "[" + std::to_string(m_len) + "]";
		for (int i = 0; i < m_len; ++i)
		{
			if (i == 0)
			{
				reply += "{";
			}
			else
			{
				reply += ",";
			}
			reply += std::to_string((int)m_bytes[i]);
		}
		reply += "}";
		return reply;
	}

private:
	unsigned char* m_bytes;
	size_t m_len;
};

