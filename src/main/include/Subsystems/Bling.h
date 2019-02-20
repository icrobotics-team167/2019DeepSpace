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

    /*
    static const double SOLID_PINK;
    static const double SOLID_RED;
    static const double SOLID_ORANGE;
    static const double SOLID_GOLD;
    static const double SOLID_YELLOW;
    static const double SOLID_GREEN;
    static const double SOLID_BLUE;
    static const double SOLID_VIOLET;
    static const double SOLID_WHITE;
    */
};

#endif