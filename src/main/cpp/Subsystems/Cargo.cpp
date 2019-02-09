#include "Subsystems/Cargo.h"

Cargo::Cargo() {
    // Cargo intake
    armTalon = new TalonSRX(CARGO_ARM_TALON);
    intakeTalon = new TalonSRX(CARGO_INTAKE_TALON);
    lightSensor = new frc::AnalogInput(CARGO_LIGHT_SENSOR);

    // Cargo out
    leftOutTalon = new TalonSRX(CARGO_LEFT_OUT_TALON);
    rightOutTalon = new TalonSRX(CARGO_RIGHT_OUT_TALON);
}

Cargo::~Cargo() {
    // Cargo intake
    delete armTalon;
    delete intakeTalon;
    delete lightSensor;

    // Cargo out
    delete leftOutTalon;
    delete rightOutTalon;
}