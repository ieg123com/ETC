#pragma once
#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif // !_WIN32

#include "CJsonObject.hpp"

class ejson :public neb::CJsonObject
{
public:
	bool open(const char* file);//打开并解析文件

//	neb::CJsonObject m_json;

};


