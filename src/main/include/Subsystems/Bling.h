#ifndef BLING_H
#define BLING_H

#include "RobotMap.h"

#include <frc/WPILib.h>

class Bling {
private:
    // Blinkins
    frc::Spark *leftBlinkin;
    frc::Spark *rightBlinkin;
public:
    Bling();
    ~Bling();
    void runLeftLEDStrip(double pattern);
    void runRightLEDStrip(double pattern);

    const double SOLID_PINK = 0.57;
    const double SOLID_RED = 0.61;
    const double SOLID_ORANGE = 0.61;
    const double SOLID_GOLD = 0.67;
    const double SOLID_YELLOW = 0.69;
    const double SOLID_GREEN = 0.77;
    const double SOLID_BLUE = 0.87;
    const double SOLID_VIOLET = 0.91;
    const double SOLID_WHITE = 0.93;
};

#endif