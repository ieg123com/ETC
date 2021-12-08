#include "hex.h"
#include <string.h>

char buf_str[] = "0123456789ABCDEF";

char Base64StrToChar(const char str);

std::string hex_encode(const void* data, const int size)
{
	std::string ret;
	if (!data || size <= 0)
		return std::move(ret);
	ret.resize(size * 2 );
	char* pos_ret = &ret[0];
	char* pos = (char*)data;
	for (int i = 0; i < size; ++i)
	{
		(*(pos_ret++)) = buf_str[(pos[i] & 0XF0) >> 4];
		(*(pos_ret++)) = buf_str[pos[i] & 0x0F];
	}
	return std::move(ret);
}

std::string hex_decode(const std::string& hex_str)
{
	std::string ret;
	size_t size = hex_calc_size(hex_str);
	if (size == 0)
	{
		return std::move(ret);
	}
	ret.resize(size);

	hex_decode(hex_str, (void*)ret[0], size);
	return std::move(ret);
}

void hex_decode(const std::string& base16_str, void* back_data, const int buf_size)
{
	hex_decode(base16_str.c_str(), base16_str.size(), back_data, buf_size);
}

void hex_decode(const char* base16_str, const int str_len, void* back_data, const int buf_size)
{
	int len = str_len / 2;
	if (len > buf_size)
		len = buf_size;
	memset(back_data, 0, buf_size);
	const char* pos_str = base16_str;
	char* pos_back_data = (char*)back_data;
	for (int i = 0; i < len; ++i)
	{
		pos_back_data[i] = (Base64StrToChar(*(pos_str)++) << 4);
		pos_back_data[i] |= Base64StrToChar(*(pos_str)++);
	}
		
}

size_t hex_calc_size(const std::string& hex_code)
{
	return hex_code.size() / 2;
}


char Base64StrToChar(const char str)
{
	switch (str)
	{
	case '0':	return 0;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':case 'a':	return 10;
	case 'B':case 'b':	return 11;
	case 'C':case 'c':	return 12;
	case 'D':case 'd':	return 13;
	case 'E':case 'e':	return 14;
	case 'F':case 'f':	return 15;
	}
	return 0;
}