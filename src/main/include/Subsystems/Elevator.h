#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "RobotMap.h"

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class Elevator {
private:
    // Elevator motor
    TalonSRX *talon;

    // Elevator encoder
    frc::Encoder *encoder;

    // Elevator limit switches
    frc::DigitalInput *bottomLimitSwitch;
    frc::DigitalInput *middleLimitSwitch;
    frc::DigitalInput *topLimitSwitch;
public:
    Elevator();
    ~Elevator();
    void raiseElevator(double speed);
    void lowerElevator(double speed);
};

#endif