#pragma once
#include <string>
#include <sstream>
#include <vector>


namespace std
{
	// 分割字符
	// @text		要分割的字符
	// @target_text	分割的字符
	std::vector<std::string> split(const std::string& text,const std::string& target_text);

	
	template<typename T>
	T to(const std::string& text) {
		T ret_num = 0;
		std::stringstream ss;
		ss << text;
		ss >> ret_num;
		return ret_num;
	}

	std::string Print(const char* format, ...);
	std::string PrintToUtf8(const char* format, ...);

	std::string format(const std::string& fmt, ...);


	std::string gb2312_to_utf8(const std::string& text);
	std::string utf8_to_gb2312(const std::string& text);

}