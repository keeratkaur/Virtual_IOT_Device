#include "app/device_manager.h"
#include "app/logger.h"
#include "app/telemetry_queue.h"
#include "hal/hal_network.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdint>
#include <string>
#include <thread>
#include <vector>

namespace {

Telemetry make_telemetry(const std::string& device_id, float temperature_c, std::uint64_t timestamp) {
    Telemetry t{};
    t.device_id = device_id;
    t.temperature_c = temperature_c;
    t.timestamp = timestamp;

    if (temperature_c > 35.0f) {
        t.status = "error";
    } else if (temperature_c > 30.0f) {
        t.status = "warning";
    } else {
        t.status = "normal";
    }

    return t;
}

void sensor_task(std::atomic<bool>& stop,
                 TelemetryQueue& queue,
                 const std::string& device_id,
                 std::chrono::milliseconds period) {
    DeviceManager device(device_id);
    device.init();

    std::uint64_t timestamp = 0;

    while (!stop.load()) {
        float temperature_c = device.read_temperature_c();

        // Local log level mirrors what would typically happen in a sensor task.
        if (temperature_c > 35.0f) {
            LOG_ERROR("[%s] Overheat: %0.1f C", device_id.c_str(), temperature_c);
        } else if (temperature_c > 30.0f) {
            LOG_WARN("[%s] Temperature high: %0.1f C", device_id.c_str(), temperature_c);
        } else {
            LOG_INFO("[%s] Temperature: %0.1f C", device_id.c_str(), temperature_c);
        }

        queue.push(make_telemetry(device_id, temperature_c, ++timestamp));

        std::this_thread::sleep_for(period);
    }
}

void network_task(std::atomic<bool>& stop, TelemetryQueue& queue) {
    HAL_Network::init();

    Telemetry t{};
    while (queue.pop(t)) {
        if (stop.load()) {
            // Allow a fast exit once stop is requested.
            // (Remaining items are intentionally dropped.)
            break;
        }

        char buf[256];
        std::snprintf(buf, sizeof(buf),
                      "{\"device_id\":\"%s\",\"temp\":%.2f,\"timestamp\":%llu,\"status\":\"%s\"}",
                      t.device_id.c_str(),
                      static_cast<double>(t.temperature_c),
                      static_cast<unsigned long long>(t.timestamp),
                      t.status.c_str());

        HAL_Network::send(buf);
    }
}

} // namespace

int main() {
    Logger::init();

    TelemetryQueue queue;
    std::atomic<bool> stop{false};

    // Run for a finite number of cycles so it’s easy to test.
    // Set to 0 to run forever.
    constexpr std::uint64_t max_sensor_cycles = 25;

    // Simulate multiple RTOS "sensor tasks".
    std::vector<std::thread> threads;
    threads.emplace_back(sensor_task, std::ref(stop), std::ref(queue), std::string("VIRT001"), std::chrono::milliseconds(1000));
    threads.emplace_back(sensor_task, std::ref(stop), std::ref(queue), std::string("VIRT002"), std::chrono::milliseconds(1000));
    threads.emplace_back(sensor_task, std::ref(stop), std::ref(queue), std::string("VIRT003"), std::chrono::milliseconds(1000));

    // One RTOS "network task" consuming telemetry.
    threads.emplace_back(network_task, std::ref(stop), std::ref(queue));

    if (max_sensor_cycles != 0) {
        // Approximate runtime: max_sensor_cycles * 1s, then stop.
        std::this_thread::sleep_for(std::chrono::seconds(max_sensor_cycles));
        stop.store(true);
        queue.close();
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

