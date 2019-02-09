#ifndef BLING_H
#define BLING_H

#include "RobotMap.h"

#include <frc/WPILib.h>

class Bling {
private:
    // LEDs
    frc::DigitalOutput *leftLED;
    frc::DigitalOutput *rightLED;

    // Line-tracking sensors
    frc::AnalogInput *lightSensorLeft;
    frc::AnalogInput *lightSensorMiddle;
    frc::AnalogInput *lightSensorRight;
public:
    Bling();
    ~Bling();
};

#endif