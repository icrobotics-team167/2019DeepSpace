#include "Controls/DoubleXboxController.h"

DoubleXboxController::DoubleXboxController() {
    xboxController1 = new frc::XboxController(0);
    xboxController2 = new frc::XboxController(1);
}

DoubleXboxController::~DoubleXboxController() {
    delete xboxController1;
    delete xboxController2;
}

double DoubleXboxController::getDrivetrainLeftSpeed() {
    double left1Y = -xboxController1->GetY(frc::Joystick::JoystickHand::kLeftHand);
    if (left1Y >= DRIVETRAIN_DEADZONE || left1Y <= -DRIVETRAIN_DEADZONE) {
        return left1Y;
    }
    return 0;
}

double DoubleXboxController::getDrivetrainRightSpeed() {
    double right1Y = -xboxController1->GetY(frc::Joystick::JoystickHand::kRightHand);
    if (right1Y >= DRIVETRAIN_DEADZONE || right1Y <= -DRIVETRAIN_DEADZONE) {
        return right1Y;
    }
    return 0;
}

bool DoubleXboxController::getOpenClaw() {
    return xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3;
}

bool DoubleXboxController::getCloseClaw() {
    return xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

bool DoubleXboxController::getSetHighGear() {
    return xboxController1->GetBumper(frc::Joystick::JoystickHand::kRightHand);
}

bool DoubleXboxController::getSetLowGear() {
    return xboxController1->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

bool DoubleXboxController::getRaiseClaw() {
    return xboxController1->GetAButton();
}

bool DoubleXboxController::getLowerClaw() {
    return xboxController1->GetBButton();
}

double DoubleXboxController::getElevatorSpeed() {
    double right2Y = xboxController2->GetY(frc::Joystick::JoystickHand::kRightHand);
    if(right2Y >= ELEVATOR_DEADZONE || right2Y <= -ELEVATOR_DEADZONE) {
        return right2Y;
    }
    return 0;
}

bool DoubleXboxController::getRunFrontOut() {
    return xboxController2->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

bool DoubleXboxController::getRunBackOut() {
    return xboxController2->GetBumper(frc::Joystick::JoystickHand::kRightHand);
}

bool DoubleXboxController::getRunIntake() {
    return xboxController2->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

bool DoubleXboxController::getSetLimelightVision() {
    return xboxController1->GetStartButton();
}

bool DoubleXboxController::getSetLimelightCamera() {
    return xboxController1->GetBackButton();
}