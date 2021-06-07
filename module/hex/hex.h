#pragma once
#include <string>

// 用于16进制转换

std::string hex_encode(const void* data, const int size);
std::string hex_decode(const std::string& hex_str);
void hex_decode(const std::string& base16_str, void* back_data, const int buf_size);
void hex_decode(const char* base16_str, const int str_len, void* back_data, const int buf_size);
size_t hex_calc_size(const std::string& hex_code);	// 计算大小
