#include "hal_network.h"

#include <iostream>

void HAL_Network::init() {
    // Host build: nothing to initialize yet.
}

void HAL_Network::send(const char* message) {
    // For now just print to stdout with a [NET] prefix to simulate
    // a network/backend consumer.
    std::cout << "[NET] " << message << std::endl;
}

