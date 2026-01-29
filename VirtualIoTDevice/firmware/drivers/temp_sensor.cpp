#include "temp_sensor.h"

void TempSensor::init() {
    // Simulated sensor init
}

float TempSensor::read_temperature() {
    static float temp = 22.0f;
    temp += 0.2f;
    // Let the simulated temperature ramp high enough to trigger
    // WARN/ERROR paths in firmware, then wrap around.
    if (temp > 40.0f) temp = 22.0f;
    return temp;
}

