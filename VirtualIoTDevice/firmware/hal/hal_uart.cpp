#include "hal_uart.h"
#include <iostream>

void HAL_UART::init() {
    // Simulated UART initialization (no-op for host build)
}

void HAL_UART::write(const std::string& msg) {
    // Simulated UART transmit using standard output.
    std::cout << msg;
}

