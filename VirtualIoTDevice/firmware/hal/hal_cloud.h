#pragma once

// Stub for a "cloud" or remote logging transport.
// For now this is just a placeholder to keep firmware code
// hardware- and transport-agnostic. Implementation can later
// be replaced with a real socket / cloud client.

namespace HAL_Cloud {

    // Initialize cloud transport (no-op in the host build).
    void init();

    // Send a single log line to the cloud (no-op for now).
    void send_log(const char* line);
}

