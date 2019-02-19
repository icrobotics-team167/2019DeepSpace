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
    void RunLeftLEDStrip(double pattern);
    void RunRightLEDStrip(double pattern);
};

#endif