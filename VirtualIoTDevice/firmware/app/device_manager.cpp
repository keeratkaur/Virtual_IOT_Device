#include "device_manager.h"
#include <iostream>

void DeviceManager::init() {
    temp_sensor_.init();
}

void DeviceManager::run() {
    float temp = temp_sensor_.read_temperature();
    std::cout << "[FW] Temperature: " << temp << " C" << std::endl;
}

