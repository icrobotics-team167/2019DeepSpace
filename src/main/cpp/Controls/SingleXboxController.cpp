#include "Controls/SingleXboxController.h"

SingleXboxController::SingleXboxController() {
    xboxController = new frc::XboxController(0);
}

SingleXboxController::~SingleXboxController() {
    delete xboxController;
}

double SingleXboxController::getDrivetrainLeftSpeed() {
    return -xboxController->GetY(frc::Joystick::JoystickHand::kLeftHand);
}

double SingleXboxController::getDrivetrainRightSpeed() {
    return -xboxController->GetY(frc::Joystick::JoystickHand::kRightHand);
}

bool SingleXboxController::getOpenClaw() {
    if (xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3) {
        return true;
    }
    return false;
}

bool SingleXboxController::getCloseClaw() {
    if (xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3) {
        return true;
    }
    return false;
}

bool SingleXboxController::getSetHighGear() {
    if (xboxController->GetBumper(frc::Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    return false;
}

bool SingleXboxController::getSetLowGear() {
    if (xboxController->GetBumper(frc::Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    return false;
}

bool SingleXboxController::getRaiseClaw() {
    if (xboxController->GetAButton()) {
        return true;
    }
    return false;
}

bool SingleXboxController::getLowerClaw() {
    if (xboxController->GetBButton()) {
        return true;
    }
    return false;
}

bool SingleXboxController::getRaiseElevator() {
    if (xboxController->GetXButton()) {
        return true;
    }
    return false;
}

bool SingleXboxController::getLowerElevator() {
    if (xboxController->GetYButton()) {
        return true;
    }
    return false;
}

bool SingleXboxController::getRunFrontOut() {
    if (xboxController->GetStickButton(frc::Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    return false;
}

bool SingleXboxController::getRunBackOut() {
    if (xboxController->GetStickButton(frc::Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    return false;
}

bool SingleXboxController::getRunIntake() {
    if (xboxController->GetStartButton()) {
        return true;
    }
    return false;
}