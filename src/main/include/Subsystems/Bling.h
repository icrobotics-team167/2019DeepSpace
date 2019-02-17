#ifndef BLING_H
#define BLING_H

#include "RobotMap.h"

#include <frc/WPILib.h>

class Bling {
private:
    // Blinkin
    frc::Spark *blinkin;
    double patternVal;
public:
    Bling();
    ~Bling();
    void RunLEDStrip(double pattern);
};

#endif