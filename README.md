# Virtual IoT Device

Minimal firmware-style virtual device grown step by step like real embedded firmware. Each step adds a layer (logging, network telemetry, multi-device, RTOS-style tasks) that maps to real IoT/embedded concepts.

---

## Step 1 – Firmware Skeleton

Minimal "bare-metal style" loop with:

- main loop
- HAL time delay (`HAL_Time::delay_ms`)
- device manager (`DeviceManager`)
- simulated temperature sensor (`TempSensor`)

---

## Step 2 – UART HAL + Logging

UART-based logging and abstraction layer:

- **HAL_UART** for UART-style output abstraction.
- **Logger** with log levels and printf-style API:
  - `LOG_INFO(...)`, `LOG_WARN(...)`, `LOG_ERROR(...)`
- All firmware logs go through `Logger` → `HAL_UART`, not `std::cout`.
- Stubbed **HAL_Cloud** for future cloud/socket transport.
- Optional loop control in `main.cpp` for finite-run tests.

---

## Step 3 – Simulated Network / Cloud Telemetry

The virtual device “talks” to a simulated backend and supports multiple devices:

- **HAL_Network** (`hal_network.h/.cpp`) – simple network HAL; `send(const char*)` prints `[NET] ...` to stdout.
- **DeviceManager** takes a `device_id`; multiple devices (e.g. VIRT001, VIRT002, VIRT003) run in the main loop.
- **WARN / ERROR** log levels by temperature:
  - temp &gt; 30°C → `[WARN] ... High temperature`
  - temp &gt; 35°C → `[ERROR] ... Overheat`
- **JSON telemetry** over `HAL_Network` with `device_id`, `temp`, `timestamp`, and `status`:
  - `{"device_id":"VIRT001","temp":22.20,"timestamp":1,"status":"normal"}`  
  - `status` is `"normal"` | `"warning"` | `"error"` based on temperature.

---

## Step 5 – RTOS Task Model (Simulation)

Simulate an RTOS-style firmware architecture (without FreeRTOS):

- **Telemetry** struct: `device_id`, `temperature_c`, `timestamp`, `status`.
- **TelemetryQueue** – thread-safe queue (`std::mutex` + `std::condition_variable`), maps conceptually to `xQueueSend` / `xQueueReceive`.
- **Sensor tasks** (one per device): run at fixed interval (e.g. 1s), read temperature, log INFO/WARN/ERROR, push `Telemetry` into the queue.
- **Network task**: blocks on the queue, pops telemetry, sends JSON via `HAL_Network`.
- **Thread-safe output**: mutex-protected UART and network printing so logs don’t interleave.
- **main** acts as the “scheduler”: starts sensor threads + network thread, then joins them (finite run via `max_sensor_cycles` in code).

---

## Build and run

From `VirtualIoTDevice/firmware`:

```bash
mkdir -p build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./firmware.exe
```

Requires C++17 and a threading library (CMake `find_package(Threads)`).
