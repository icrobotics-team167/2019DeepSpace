#include "Controls/SingleXboxController.h"

SingleXboxController::SingleXboxController() {
    xboxController = new frc::XboxController(0);
}

SingleXboxController::~SingleXboxController() {
    delete xboxController;
}

double SingleXboxController::getDrivetrainLeftSpeed() {
    double leftY = -xboxController->GetY(frc::Joystick::JoystickHand::kLeftHand);
    if (leftY >= DRIVETRAIN_DEADZONE || leftY <= -DRIVETRAIN_DEADZONE) {
        return leftY;
    }
    return 0;
}

double SingleXboxController::getDrivetrainRightSpeed() {
    double rightY = -xboxController->GetY(frc::Joystick::JoystickHand::kRightHand);
    if (rightY >= DRIVETRAIN_DEADZONE || rightY <= DRIVETRAIN_DEADZONE) {
        return rightY;
    }
    return 0;
}

bool SingleXboxController::getOpenClaw() {
    return xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3;
}

bool SingleXboxController::getCloseClaw() {
    return xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

bool SingleXboxController::getSetHighGear() {
    return xboxController->GetBumper(frc::Joystick::JoystickHand::kRightHand);
}

bool SingleXboxController::getSetLowGear() {
    return xboxController->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

bool SingleXboxController::getRaiseClaw() {
    return xboxController->GetAButton();
}

bool SingleXboxController::getLowerClaw() {
    return xboxController->GetBButton();
}

double SingleXboxController::getElevatorSpeed() {
    if (xboxController->GetXButton()) {
        return 1;
    }
    if (xboxController->GetYButton()) {
        return -1;
    }
    return 0;
}

bool SingleXboxController::getRunFrontOut() {
    return xboxController->GetStickButton(frc::Joystick::JoystickHand::kLeftHand);
}

bool SingleXboxController::getRunBackOut() {
    return xboxController->GetStickButton(frc::Joystick::JoystickHand::kRightHand);
}

bool SingleXboxController::getRunIntake() {
    return xboxController->GetStartButton();
}

bool SingleXboxController::getSetLimelightVision() {
    return false;
}

bool SingleXboxController::getSetLimelightCamera() {
    return false;
}