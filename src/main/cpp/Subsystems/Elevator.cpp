#include "Subsystems/Elevator.h"

Elevator::Elevator() {
    // Elevator motor
    talon = new TalonSRX(ELEVATOR_TALON);

    // Elevator encoder
    encoder = new frc::Encoder(ELEVATOR_ENCODER_A, ELEVATOR_ENCODER_B, false);

    // Elevator limit switches
    bottomLimitSwitch = new frc::DigitalInput(ELEVATOR_LIMIT_SWITCH_BOTTOM);
    middleLimitSwitch = new frc::DigitalInput(ELEVATOR_LIMIT_SWITCH_MIDDLE);
    topLimitSwitch = new frc::DigitalInput(ELEVATOR_LIMIT_SWITCH_TOP);
}

Elevator::~Elevator() {
    // Elevator motor
    delete talon;

    // Elevator encoder
    delete encoder;

    // Elevator limit switches
    delete bottomLimitSwitch;
    delete middleLimitSwitch;
    delete topLimitSwitch;
}

void Elevator::raiseElevator(double speed) {
    talon->Set(ControlMode::PercentOutput, speed);
}

void Elevator::lowerElevator(double speed) {
    talon->Set(ControlMode::PercentOutput, -speed);
}