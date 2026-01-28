#include "app/device_manager.h"
#include "app/logger.h"
#include "hal/hal_time.h"

int main() {
    Logger::init();

    DeviceManager device;
    device.init();

    constexpr unsigned int max_iterations = 0; // 0 => run forever (firmware style)
    unsigned int iteration = 0;

    while (max_iterations == 0 || iteration < max_iterations) {
        device.run();
        HAL_Time::delay_ms(1000);
        ++iteration;
    }

    return 0;
}

