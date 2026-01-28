#include "app/logger.h"
#include "hal/hal_uart.h"
#include "hal/hal_cloud.h"

#include <array>
#include <cstdarg>
#include <cstdio>
#include <string>

namespace {

constexpr std::size_t kLogBufferSize = 256;

const char* level_to_prefix(Logger::Level level) {
    switch (level) {
        case Logger::Level::Info:  return "[INFO]";
        case Logger::Level::Warn:  return "[WARN]";
        case Logger::Level::Error: return "[ERROR]";
        default:                   return "[UNKWN]";
    }
}

} // namespace

void Logger::init() {
    HAL_UART::init();
    HAL_Cloud::init();
}

void Logger::log(Level level, const char* fmt, ...) {
    std::array<char, kLogBufferSize> buffer{};

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
    va_end(args);

    // Prefix with level and send via UART HAL.
    std::string line = std::string(level_to_prefix(level)) + " " + buffer.data();

    HAL_UART::write(line);
    HAL_UART::write("\n");

    // Also forward to the (stubbed) cloud transport.
    HAL_Cloud::send_log(line.c_str());
}



