#include "Subsystems/Cargo.h"

Cargo::Cargo() {
    // Cargo intake
    armTalon = new TalonSRX(CARGO_ARM_TALON);
    intakeTalon = new TalonSRX(CARGO_INTAKE_TALON);
    lightSensor = new frc::AnalogInput(CARGO_LIGHT_SENSOR);

    // Cargo out
    frontOutTalon = new TalonSRX(CARGO_LEFT_OUT_TALON);
    backOutTalon = new TalonSRX(CARGO_RIGHT_OUT_TALON);
}

Cargo::~Cargo() {
    // Cargo intake
    delete armTalon;
    delete intakeTalon;
    delete lightSensor;

    // Cargo out
    delete frontOutTalon;
    delete backOutTalon;
}

void Cargo::runIntake(double speed) {
    intakeTalon->Set(ControlMode::PercentOutput, speed);
}

void Cargo::stopIntake() {
    intakeTalon->Set(ControlMode::PercentOutput, 0);
}

void Cargo::runFrontOut(double speed) {
    frontOutTalon->Set(ControlMode::PercentOutput, speed);
}

void Cargo::stopFrontOut() {
    frontOutTalon->Set(ControlMode::PercentOutput, 0);
}

void Cargo::runBackOut(double speed) {
    backOutTalon->Set(ControlMode::PercentOutput, speed);
}

void Cargo::stopBackOut() {
    backOutTalon->Set(ControlMode::PercentOutput, 0);
}