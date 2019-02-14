#include "controls/XboxController.h"

XboxController::XboxController() {
    wpiController = new frc::XboxController(0);
}

XboxController::~XboxController() {
    delete wpiController;
}

double XboxController::getDrivetrainLeftSpeed() {
    return -wpiController->GetY(Joystick::JoystickHand::kLeftHand);
}

double XboxController::getDrivetrainRightSpeed() {
    return -wpiController->GetY(Joystick::JoystickHand::kRightHand);
}

bool XboxController::getOpenClaw() {
    if (wpiController->GetTriggerAxis(Joystick::JoystickHand::kRightHand) > 0.3) {
        return true;
    }
    else return false;
}

bool XboxController::getCloseClaw() {
    if (wpiController->GetTriggerAxis(Joystick::JoystickHand::kLefttHand) > 0.3) {
        return true;
    }
    else return false;
}

bool XboxController::getSetHighGear() {
    if (wpiController->GetBumper(Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    else return false;
}

bool XboxController::getSetLowGear() {
    if (wpiController->GetBumper(Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    else return false;
}

bool XboxController::getRaiseClaw() {
    if (wpiController->GetAButton()) {
        return true;
    }
    else return false;
}

bool XboxController::getLowerClaw() {
    if (wpiController->GetBButton()) {
        return true;
    }
    else return false;
}

bool XboxController::getRaiseElevator() {
    if (wpiController->GetXButton()) {
        return true;
    }
    else return false;
}

bool XboxController::getLowerElevator() {
    if (wpiController->GetYButton()) {
        return true;
    }
    else return false;
}

bool XboxController::getRunFrontOut() {
    if (wpiController->GetStickButton(Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    else return false;
}

bool XboxController::getRunBackOut() {
    if (wpiController->GetStickButton(Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    else return false;
}

bool XboxController::getRunIntake() {
    if (wpiController->GetStartButton()) return true;
    else return false;
}