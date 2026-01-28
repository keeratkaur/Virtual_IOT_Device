#pragma once

namespace Logger {

    enum class Level {
        Info,
        Warn,
        Error
    };

    // Initialize logging backend (UART, cloud stub, etc.).
    void init();

    // Core printf-style logging API.
    // Example: log(Level::Info, "[FW] Temperature: %0.1f C", temp);
    void log(Level level, const char* fmt, ...);
}

// Firmware-style convenience macros.
#define LOG_INFO(fmt, ...)  ::Logger::log(::Logger::Level::Info,  fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  ::Logger::log(::Logger::Level::Warn,  fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) ::Logger::log(::Logger::Level::Error, fmt, ##__VA_ARGS__)

