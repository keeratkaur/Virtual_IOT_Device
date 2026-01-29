#include "app/device_manager.h"
#include "app/logger.h"
#include "hal/hal_time.h"
#include <vector>

int main() {
    Logger::init();

    // Simulate multiple virtual IoT devices with unique IDs.
    std::vector<DeviceManager> devices;
    devices.emplace_back("VIRT001");
    devices.emplace_back("VIRT002");
    devices.emplace_back("VIRT003");

    // Initialize all devices.
    for (auto& device : devices) {
        device.init();
    }

    constexpr unsigned int max_iterations = 0; // 0 => run forever (firmware style)
    unsigned int iteration = 0;

    while (max_iterations == 0 || iteration < max_iterations) {
        // Run all devices in sequence (simulating parallel operation).
        for (auto& device : devices) {
            device.run();
        }
        HAL_Time::delay_ms(1000);
        ++iteration;
    }

    return 0;
}

