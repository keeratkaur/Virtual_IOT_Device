#include "telemetry_queue.h"

void TelemetryQueue::push(Telemetry t) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (closed_) {
            return;
        }
        queue_.push(std::move(t));
    }
    cv_.notify_one();
}

void TelemetryQueue::close() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        closed_ = true;
    }
    cv_.notify_all();
}

bool TelemetryQueue::pop(Telemetry& out) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&] { return closed_ || !queue_.empty(); });

    if (queue_.empty()) {
        return false;
    }

    out = std::move(queue_.front());
    queue_.pop();
    return true;
}

