#include "str.h"
#include <sstream>
#include <stdarg.h>
#include <windows.h>
#include <winnls.h>


std::vector<std::string> std::split(const std::string& text, const std::string& target_text)
{
	std::vector<std::string> all_text;
	if (text.empty())
	{
		return all_text;
	}

	if (target_text.empty())
	{
		all_text.push_back(text);
		return all_text;
	}

	size_t begin_pos = 0;
	size_t pos = std::string::npos;
	std::string new_text;
	while (pos != begin_pos)
	{
		pos = text.find(target_text, begin_pos);
		if (pos == std::string::npos)
		{
			new_text = text.substr(begin_pos, text.size() - begin_pos);
			all_text.push_back(new_text);
			break;
		}
		new_text = text.substr(begin_pos, pos - begin_pos);
		all_text.push_back(new_text);

		begin_pos = pos + target_text.size();
	}
	return all_text;
}


std::string std::Print(const char* format, ...)
{
	static std::vector<char>	vsprintf_data;
	if (vsprintf_data.empty())
	{
		vsprintf_data.resize(1024);
	}
	va_list ap;
	va_start(ap, format);
	int ret;
	while ((ret = vsnprintf(vsprintf_data.data(), vsprintf_data.size(), format, ap)) > vsprintf_data.size())
	{
		vsprintf_data.resize(vsprintf_data.size() * 2);
		va_start(ap, format);
	}
	va_end(ap);
	return std::string(vsprintf_data.data(), ret);
}


std::string std::gb2312_to_utf8(const std::string& text)
{
	int len = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string ret = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return ret;
}

std::string std::utf8_to_gb2312(const std::string& text)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	std::string ret = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return ret;
}