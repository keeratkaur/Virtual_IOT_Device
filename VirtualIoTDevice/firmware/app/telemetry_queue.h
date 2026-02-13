#pragma once

#include "app/telemetry.h"

#include <condition_variable>
#include <mutex>
#include <queue>

class TelemetryQueue {
public:
    void push(Telemetry t);
    // Close the queue and wake any blocked consumers.
    void close();

    // Blocks until an item is available or the queue is closed.
    // Returns false when closed and empty.
    bool pop(Telemetry& out);

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<Telemetry> queue_;
    bool closed_ = false;
};

