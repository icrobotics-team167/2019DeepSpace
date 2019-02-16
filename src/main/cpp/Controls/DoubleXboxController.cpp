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
    double yVal = -xboxController1->GetY(frc::Joystick::JoystickHand::kLeftHand);
    if (yVal >= DRIVETRAIN_DEADZONE || yVal <= -DRIVETRAIN_DEADZONE) {
        return yVal;
    }
    return 0;
}

double DoubleXboxController::getDrivetrainRightSpeed() {
    double yVal = -xboxController1->GetY(frc::Joystick::JoystickHand::kRightHand);
    if (yVal >= DRIVETRAIN_DEADZONE || yVal <= -DRIVETRAIN_DEADZONE) {
        return yVal;
    }
    return 0;
}

bool DoubleXboxController::getOpenClaw() {
    if (xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getCloseClaw() {
    if (xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getSetHighGear() {
    if (xboxController1->GetBumper(frc::Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getSetLowGear() {
    if (xboxController1->GetBumper(frc::Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getRaiseClaw() {
    if (xboxController1->GetAButton()) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getLowerClaw() {
    if (xboxController1->GetBButton()) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getRaiseElevator() {
    /*
    if (xboxController2->getXButton()) {
        return true;
    }
    */
    return false;
}

bool DoubleXboxController::getLowerElevator() {
    /*
    if (xboxController2->GetYButton()) {
        return true;
    }
    */
    return false;
}

double  DoubleXboxController::getElevatorSpeed() {
    double stickY = xboxController2->GetY(frc::Joystick::JoystickHand::kRightHand);
    if(stickY >= 0.3 || stickY <= -0.3) {
        return stickY;
    }
    return 0;
}

bool DoubleXboxController::getRunFrontOut() {
    if (xboxController2->GetBumper(frc::Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getRunBackOut() {
    if (xboxController2->GetBumper(frc::Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    return false;
}

bool DoubleXboxController::getRunIntake() {
    if (xboxController2->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3) {
        return true;
    }
    return false;
}