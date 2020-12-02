#pragma once

#include "./include/spdlog/spdlog/spdlog.h"
#include "./include/spdlog/spdlog/sinks/stdout_color_sinks.h"
#include "./include/spdlog/spdlog/sinks/basic_file_sink.h"
#include "./include/spdlog/spdlog/sinks/rotating_file_sink.h"
#include "./include/spdlog/spdlog/sinks/daily_file_sink.h"
#include "./include/spdlog/spdlog/fmt/bin_to_hex.h"
#include "./include/spdlog/spdlog/async.h"
#include "./include/spdlog/spdlog/fmt/fmt.h"

#ifdef _DEBUG
#pragma comment(lib,"../Public/lib/debug/spdlog.lib")
#else
#pragma comment(lib,"../Public/lib/release/spdlog.lib")
#endif
