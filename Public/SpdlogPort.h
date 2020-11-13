#pragma once

#include "include/spdlog/spdlog.h"
#include "include/spdlog/sinks/stdout_color_sinks.h"
#include "include/spdlog/sinks/basic_file_sink.h"
#include "include/spdlog/sinks/rotating_file_sink.h"
#include "include/spdlog/sinks/daily_file_sink.h"
#include "include/spdlog/fmt/bin_to_hex.h"
#include "include/spdlog/async.h"
#include "include/spdlog/fmt/fmt.h"

#ifdef _DEBUG
#pragma comment(lib,"../Public/lib/debug/spdlog.lib")
#else
#pragma comment(lib,"../Public/lib/release/spdlog.lib")
#endif
