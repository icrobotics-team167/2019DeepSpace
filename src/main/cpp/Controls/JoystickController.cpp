/*
#include "Controls/JoystickController.h"

JoystickController::JoystickController() {
    leftJoystick = new frc::Joystick(0);
    rightJoystick = new frc::Joystick(1);
}

JoystickController::~JoystickController() {
    delete leftJoystick;
    delete rightJoystick;
}

double JoystickController::getDrivetrainLeftSpeed() {
    return -leftJoystick->GetY(frc::Joystick::JoystickHand::kLeftHand);
}

double JoystickController::getDrivetrainRightSpeed() {
    return -rightJoystick->GetY(frc::Joystick::JoystickHand::kRightHand);
}

bool JoystickController::getOpenClaw() {
    if (rightJoystick->GetTrigger()) {
        return true;
    }
    return false;
}

bool JoystickController::getCloseClaw() {
    if (leftJoystick->GetTrigger()) {
        return true;
    }
    return false;
}

bool JoystickController::getSetHighGear() {
    if (rightJoystick->GetRawButton(2)) {
        return true;
    }
    return false;
}

bool JoystickController::getSetLowGear() {
    if (leftJoystick->GetRawButton(2)) {
        return true;
    }
    return false;
}

bool JoystickController::getRaiseClaw() {
    if (rightJoystick->GetRawButton(3)) {
        return true;
    }
    return false;
}

bool JoystickController::getLowerClaw() {
    if (leftJoystick->GetRawButton(3)) {
        return true;
    }
    return false;
}

double  JoystickController::getElevatorSpeed() {
    double stickY = rightJoystick->GetY(frc::Joystick::JoystickHand::kRightHand);
    if(stickY >= 0.3 || stickY <= -0.3) {
        return stickY;
    }
    return 0;
}

bool JoystickController::getRunFrontOut() {
    if (rightJoystick->GetBumper(frc::Joystick::JoystickHand::kLeftHand)) {
        return true;
    }
    return false;
}

bool JoystickController::getRunBackOut() {
    if (joystick->GetBumper(frc::Joystick::JoystickHand::kRightHand)) {
        return true;
    }
    return false;
}

bool JoystickController::getRunIntake() {
    if (joystick->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3) {
        return true;
    }
    return false;
}
*/