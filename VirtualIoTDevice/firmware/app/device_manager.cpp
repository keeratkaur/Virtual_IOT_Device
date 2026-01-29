#include "device_manager.h"
#include "app/logger.h"
#include "hal/hal_network.h"

#include <cstdio>

void DeviceManager::init() {
    temp_sensor_.init();
}

void DeviceManager::run() {
    float temp = temp_sensor_.read_temperature();

    // Local firmware log over UART.
    LOG_INFO("[FW] Temperature: %0.1f C", temp);

    // Also forward telemetry over the simulated network as JSON.
    char buf[128];
    std::snprintf(buf, sizeof(buf),
                  "{\"device_id\":\"VIRT001\",\"temp\":%.2f}", temp);

    HAL_Network::send(buf);
}

