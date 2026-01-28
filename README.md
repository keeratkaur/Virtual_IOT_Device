# Virtual IoT Device

Step 1: minimal firmware-style skeleton with:

- main loop
- HAL time delay
- device manager
- simulated temperature sensor

Build and run (from `VirtualIoTDevice/firmware`):

```bash
mkdir -p build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./firmware.exe
```

