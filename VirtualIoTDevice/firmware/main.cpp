#include "app/device_manager.h"
#include "hal/hal_time.h"

int main() {
    DeviceManager device;

    device.init();

    while (true) {
        device.run();
        HAL_Time::delay_ms(1000);
    }

    return 0;
}

