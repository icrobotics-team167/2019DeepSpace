#include "Subsystems/Bling.h"

Bling::Bling() {
    // LEDs
    leftLED = new frc::DigitalOutput(LEFT_LED);
    rightLED = new frc::DigitalOutput(RIGHT_LED);

    // Line-tracking sensors
    lightSensorLeft = new frc::AnalogInput(LIGHT_SENSOR_LEFT);
    lightSensorMiddle = new frc::AnalogInput(LIGHT_SENSOR_MIDDLE);
    lightSensorRight = new frc::AnalogInput(LIGHT_SENSOR_RIGHT);
}

Bling::~Bling() {
    // LEDs
    delete leftLED;
    delete rightLED;    

    // Line-tracking sensors
    delete lightSensorLeft;
    delete lightSensorMiddle;
    delete lightSensorRight;
}