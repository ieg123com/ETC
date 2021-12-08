#include "ejson.h"



bool ejson::open(const char* file)
{
	FILE *_fp = fopen(file, "rb");
	if (NULL == _fp)
		return false;

	struct stat _FileStat;
	fstat(fileno(_fp), &_FileStat);
	char *_buf = new char[_FileStat.st_size];

	fread(_buf, _FileStat.st_size, 1, _fp);
	if (!Parse(std::string(_buf, _FileStat.st_size)))
		return false;			//json文件读取失败
	fclose(_fp);
	delete []_buf;
	_buf = NULL;
	return true;
}


