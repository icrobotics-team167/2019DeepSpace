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
    TalonSRX *leftOutTalon;
    TalonSRX *rightOutTalon;
public:
    Cargo();
    ~Cargo();
};

#endif