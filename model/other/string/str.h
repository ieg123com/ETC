#pragma once
#include <string>
#include <vector>


namespace std
{
	// �ָ��ַ�
	// @text		Ҫ�ָ���ַ�
	// @target_text	�ָ���ַ�
	std::vector<std::string> Split(const std::string& text,const std::string& target_text);

	// �� int32_t
	int32_t to_int32(const std::string& text);

	// �� int64_t
	int64_t to_int64(const std::string& text);

	// �� double
	double to_duuble(const std::string& text);


	std::string Print(const char* format, ...);
	std::string PrintToUtf8(const char* format, ...);


	std::string gb2312_to_utf8(const std::string& text);
	std::string utf8_to_gb2312(const std::string& text);

}