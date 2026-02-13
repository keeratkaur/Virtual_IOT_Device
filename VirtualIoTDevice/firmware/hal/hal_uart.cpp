#include "hal_uart.h"
#include <iostream>
#include <mutex>

namespace {
std::mutex g_uart_mutex;
}

void HAL_UART::init() {
    // Simulated UART initialization (no-op for host build)
}

void HAL_UART::write(const std::string& msg) {
    // Simulated UART transmit using standard output.
    std::lock_guard<std::mutex> lock(g_uart_mutex);
    std::cout << msg;
}

