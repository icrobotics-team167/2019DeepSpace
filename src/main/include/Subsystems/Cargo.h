#ifndef CARGO_H
#define CARGO_H

#include "RobotMap.h"

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class Cargo {
private:
    // Cargo intake
    TalonSRX *armTalon;
    TalonSRX *intakeTalon;
    frc::AnalogInput *lightSensor;

    // Cargo out
    TalonSRX *frontOutTalon;
    TalonSRX *backOutTalon;
public:
    Cargo();
    ~Cargo();
    void runIntake(double speed);
    void stopIntake();
    void runFront(double speed);
    void stopFront();
    void runBack(double speed);
    void stopBack();
    void ejectCargo();
    void holdCargo();
    void reverseIntake();
};

#endif