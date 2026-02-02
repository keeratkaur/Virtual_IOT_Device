#pragma once
#include "drivers/temp_sensor.h"
#include <string>

class DeviceManager {
public:
    DeviceManager(const std::string& device_id);
    void init();
    const std::string& device_id() const;
    float read_temperature_c();

private:
    std::string device_id_;
    TempSensor temp_sensor_;
    float temp_offset_;
};

