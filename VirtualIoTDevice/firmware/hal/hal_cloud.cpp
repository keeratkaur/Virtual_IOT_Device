#include "hal_cloud.h"

void HAL_Cloud::init() {
    // Host build: no real cloud transport yet.
}

void HAL_Cloud::send_log(const char* /*line*/) {
    // Host build stub: intentionally do nothing for now.
    // This is where a simulated socket / cloud client would go.
}

