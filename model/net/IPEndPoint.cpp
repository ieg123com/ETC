#include "IPEndPoint.h"

std::ostream& operator << (std::ostream& output, IPEndPoint& right)
{
	return (output << right.ToString());
}