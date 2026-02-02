#pragma once

#include <cstdint>
#include <string>

struct Telemetry {
    std::string device_id;
    float temperature_c;
    std::uint64_t timestamp;
    std::string status; // "normal" | "warning" | "error"
};

