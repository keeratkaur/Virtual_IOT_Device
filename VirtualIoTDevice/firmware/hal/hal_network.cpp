#include "hal_network.h"

#include <iostream>
#include <mutex>

namespace {
std::mutex g_net_mutex;
}

void HAL_Network::init() {
    // Host build: nothing to initialize yet.
}

void HAL_Network::send(const char* message) {
    // For now just print to stdout with a [NET] prefix to simulate
    // a network/backend consumer.
    std::lock_guard<std::mutex> lock(g_net_mutex);
    std::cout << "[NET] " << message << std::endl;
}

