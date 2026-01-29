#pragma once
#include "drivers/temp_sensor.h"
#include <string>

class DeviceManager {
public:
    DeviceManager(const std::string& device_id);
    void init();
    void run();

private:
    std::string device_id_;
    TempSensor temp_sensor_;
    float temp_offset_;
};

