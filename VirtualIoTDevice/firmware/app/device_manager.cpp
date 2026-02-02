#include "device_manager.h"

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

const std::string& DeviceManager::device_id() const {
    return device_id_;
}

float DeviceManager::read_temperature_c() {
    return temp_sensor_.read_temperature() + temp_offset_;
}

