# Virtual IoT Device

Minimal firmware-style virtual device grown step by step like real embedded firmware.

## Step 1 – Firmware Skeleton

Minimal "bare-metal style" loop with:

- main loop
- HAL time delay (`HAL_Time::delay_ms`)
- device manager (`DeviceManager`)
- simulated temperature sensor (`TempSensor`)

Build and run (from `VirtualIoTDevice/firmware`):

```bash
mkdir -p build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./firmware.exe
```

## Step 2 – UART HAL + Logging

UART-based logging and abstraction layer:

- Added `HAL_UART` for UART-style output abstraction.
- Added `Logger` with log levels and printf-style API:
  - `LOG_INFO("Temperature: %0.1f C", temp);`
  - `LOG_WARN(...)`
  - `LOG_ERROR(...)`
- All firmware logs now go through `Logger` → `HAL_UART`, not `std::cout`.
- Stubbed `HAL_Cloud` so logs can later be forwarded to a simulated socket / cloud client.
- Added optional loop control (compile-time constant in `main.cpp`) to allow finite-run tests.