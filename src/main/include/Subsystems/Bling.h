#ifndef BLING_H
#define BLING_H

#include "RobotMap.h"

#include <frc/WPILib.h>

class Bling {
private:
    // Blinkin
    frc::Spark *blinkin1;
    frc::Spark *blinkin2;
    double patternVal;
public:
    Bling();
    ~Bling();
    void RunLEDStrip1(double pattern);
    void RunLEDStrip2(double pattern);
};

#endif