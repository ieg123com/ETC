#include "bytes.h"


std::ostream& operator<<(std::ostream& output, Bytes& right)
{
	output << "[" << right.m_len << "]";
	for (int i = 0; i < right.m_len; ++i)
	{
		if (i == 0)
		{
			output << "{";
		}
		else
		{
			output << ",";
		}
		output << (int)right.m_bytes[i];
	}
	output << "}";
	return output;
}