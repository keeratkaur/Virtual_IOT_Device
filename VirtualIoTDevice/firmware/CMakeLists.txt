cmake_minimum_required(VERSION 3.10)
project(VirtualIoTFirmware)

set(CMAKE_CXX_STANDARD 17)

add_executable(firmware
    main.cpp
    app/device_manager.cpp
    drivers/temp_sensor.cpp
    hal/hal_time.cpp
)

# Allow includes like "drivers/temp_sensor.h" from any translation unit.
target_include_directories(firmware PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

