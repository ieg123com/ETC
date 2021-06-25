#pragma once


#include "spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> //support for stdout logging
#include <spdlog/sinks/basic_file_sink.h> // support for basic file logging
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging


#define LOG_DEBUG(...)	spdlog::default_logger_raw()->log(spdlog::level::debug,__VA_ARGS__)

#define LOG_INFO(...)	spdlog::default_logger_raw()->log(spdlog::level::info,__VA_ARGS__)

#define LOG_WARN(...)	spdlog::default_logger_raw()->log(spdlog::level::warn,__VA_ARGS__)

#define LOG_ERROR(...)	spdlog::default_logger_raw()->log(spdlog::level::err,__VA_ARGS__)
