#include "device_manager.h"
#include "app/logger.h"

void DeviceManager::init() {
    temp_sensor_.init();
}

void DeviceManager::run() {
    float temp = temp_sensor_.read_temperature();

    LOG_INFO("[FW] Temperature: %0.1f C", temp);
}

