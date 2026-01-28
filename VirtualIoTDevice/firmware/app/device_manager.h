#pragma once
#include "drivers/temp_sensor.h"

class DeviceManager {
public:
    void init();
    void run();

private:
    TempSensor temp_sensor_;
};

