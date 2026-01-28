#pragma once

#include <string>

namespace HAL_UART {
    // Initialize the simulated UART peripheral.
    void init();

    // Write a raw string over the simulated UART.
    void write(const std::string& msg);
}

