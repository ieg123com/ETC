#pragma once


#include "spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> //support for stdout logging
#include <spdlog/sinks/basic_file_sink.h> // support for basic file logging
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging

#define COMPILE_TO_STR(_str) #_str
#define COMPILE_INT_TO_STR(_num) COMPILE_TO_STR(_num)

#define LOG_DEBUG(str,...)	spdlog::default_logger_raw()->log(spdlog::level::debug,str,__VA_ARGS__)

#define LOG_INFO(str,...)	spdlog::default_logger_raw()->log(spdlog::level::info,str,__VA_ARGS__)

#define LOG_WARN(str,...)	spdlog::default_logger_raw()->log(spdlog::level::warn,"[" __FUNCTION__ ":" COMPILE_INT_TO_STR(__LINE__) "] " str,__VA_ARGS__)

#define LOG_ERROR(str,...)	spdlog::default_logger_raw()->log(spdlog::level::err,"[" __FUNCTION__ ":" COMPILE_INT_TO_STR(__LINE__) "] " str,__VA_ARGS__)
