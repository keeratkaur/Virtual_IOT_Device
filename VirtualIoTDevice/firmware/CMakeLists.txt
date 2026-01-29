cmake_minimum_required(VERSION 3.10)
project(VirtualIoTFirmware)

set(CMAKE_CXX_STANDARD 17)

add_executable(firmware
    main.cpp
    app/device_manager.cpp
    app/logger.cpp
    drivers/temp_sensor.cpp
    hal/hal_time.cpp
    hal/hal_network.cpp
    hal/hal_uart.cpp
    hal/hal_cloud.cpp
)

# Allow includes like "drivers/temp_sensor.h" from any translation unit.
target_include_directories(firmware PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

