#ifndef CLAW_H
#define CLAW_H

#include "RobotMap.h"

#include <WPILib.h>

class Claw {
private:
    // Claw opening and closing solenoids
    frc::Solenoid *openSolenoid;
    frc::Solenoid *closedSolenoid;

    // Claw raising and lowering solenoid
    frc::Solenoid *pivotSolenoid;
public:
    Claw();
    ~Claw();
};

#endif