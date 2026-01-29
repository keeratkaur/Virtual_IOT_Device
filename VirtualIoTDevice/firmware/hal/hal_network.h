#pragma once

// Simple simulated network/HAL layer used by the firmware to
// "send" telemetry to a backend. In the host build this just
// prints to stdout with a [NET] prefix.

namespace HAL_Network {

    // Initialize network transport (no-op in the host build for now).
    void init();

    // Send a single message over the simulated network.
    void send(const char* message);
}

