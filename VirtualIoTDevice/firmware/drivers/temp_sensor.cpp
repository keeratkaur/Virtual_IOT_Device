#include "temp_sensor.h"

void TempSensor::init() {
    // Simulated sensor init
}

float TempSensor::read_temperature() {
    static float temp = 22.0f;
    temp += 0.2f;
    if (temp > 30.0f) temp = 22.0f;
    return temp;
}

