#pragma once
#include <stdint.h>



class Vector3
{
public:

	int32_t	x;
	int32_t	y;
	int32_t	z;

	bool operator == (const Vector3& val) const {
		if (x == val.x &&
			y == val.y &&
			z == val.z)
		{
			return true;
		}
		return false;
	}

};






