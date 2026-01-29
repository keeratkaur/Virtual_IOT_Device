#include "device_manager.h"
#include "app/logger.h"
#include "hal/hal_network.h"

#include <cstdio>

namespace {
    // Simple monotonically increasing timestamp used for simulated
    // network telemetry. One tick per call to DeviceManager::run().
    unsigned int g_timestamp = 0;
}

DeviceManager::DeviceManager(const std::string& device_id)
    : device_id_(device_id),
      temp_offset_(0.0f) {
    // Simple per-device temperature offset so different devices
    // naturally hit INFO/WARN/ERROR ranges at different times.
    //
    // Extract the last digit from IDs like "VIRT001", "VIRT002", ...
    unsigned int last_digit = 0;
    if (!device_id_.empty()) {
        const char c = device_id_.back();
        if (c >= '0' && c <= '9') {
            last_digit = static_cast<unsigned int>(c - '0');
        }
    }

    temp_offset_ = static_cast<float>(last_digit) * 2.5f;
}


void DeviceManager::init() {
    temp_sensor_.init();
}

void DeviceManager::run() {
    float temp = temp_sensor_.read_temperature() + temp_offset_;

    // Determine status and log level based on temperature.
    const char* status;
    if (temp > 35.0f) {
        LOG_ERROR("[%s] Overheat: %0.1f C", device_id_.c_str(), temp);
        status = "error";
    } else if (temp > 30.0f) {
        LOG_WARN("[%s] High temperature: %0.1f C", device_id_.c_str(), temp);
        status = "warning";
    } else {
        LOG_INFO("[%s] Temperature: %0.1f C", device_id_.c_str(), temp);
        status = "normal";
    }

    // Forward telemetry over the simulated network as JSON with status.
    ++g_timestamp;

    char buf[200];
    std::snprintf(buf, sizeof(buf),
                  "{\"device_id\":\"%s\",\"temp\":%.2f,\"timestamp\":%u,\"status\":\"%s\"}",
                  device_id_.c_str(),
                  temp,
                  g_timestamp,
                  status);

    HAL_Network::send(buf);
}

