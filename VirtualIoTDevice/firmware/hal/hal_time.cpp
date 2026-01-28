#include "hal_time.h"
#include <thread>
#include <chrono>

void HAL_Time::delay_ms(unsigned int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

