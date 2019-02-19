#include "Subsystems/Cargo.h"

Cargo::Cargo() {
    // Cargo intake
    armTalon = new TalonSRX(CARGO_ARM_TALON);
    intakeTalon = new TalonSRX(CARGO_INTAKE_TALON);
    lightSensor = new frc::AnalogInput(CARGO_LIGHT_SENSOR);

    // Cargo out
    backOutTalon = new TalonSRX(CARGO_BACK_OUT_TALON);
    frontOutTalon = new TalonSRX(CARGO_FRONT_OUT_TALON);
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

/**
 * Runs the intake
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @param speed The speed to run the intake
 */
void Cargo::runIntake(double speed) {
    intakeTalon->Set(ControlMode::PercentOutput, speed);
}

/**
 * Stops the intake
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */
void Cargo::stopIntake() {
    intakeTalon->Set(ControlMode::PercentOutput, 0);
}

/**
 * Runs the front cargo talon
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @param speed The speed to run the front cargo talon
 */
void Cargo::runFront(double speed) {
    frontOutTalon->Set(ControlMode::PercentOutput, speed);
}

/**
 * Stops the front cargo talon
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */
void Cargo::stopFront() {
    frontOutTalon->Set(ControlMode::PercentOutput, 0);
}

/**
 * Runs the back cargo talon
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @param speed The speed to run the back cargo talon
 */
void Cargo::runBack(double speed) {
    backOutTalon->Set(ControlMode::PercentOutput, -speed);
}

/**
 * Stops the back cargo talon
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */
void Cargo::stopBack() {
    backOutTalon->Set(ControlMode::PercentOutput, 0);
}

/**
 * Runs the front and back cargo talons to eject the cargo
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019 
 */
void Cargo::ejectCargo() {
    runFront(0.6);
    runBack(0.6);
}

/**
 * Runs the front and back cargo talons to hold on to the cargo
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */
void Cargo::holdCargo() {
    runFront(-0.6);
    runBack(0.6);
}