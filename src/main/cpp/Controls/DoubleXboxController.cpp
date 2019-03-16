#include "Controls/DoubleXboxController.h"

DoubleXboxController::DoubleXboxController() {
    xboxController1 = new frc::XboxController(0);
    xboxController2 = new frc::XboxController(1);
}

DoubleXboxController::~DoubleXboxController() {
    delete xboxController1;
    delete xboxController2;
}

/**
 * Determines whether to drive with the Limelight
 * 
 * @author Dominic Rutkowski
 * @since 2-19-2019
 * 
 * @returns True if the robot should drive with the Limelight, false otherwise
 */
bool DoubleXboxController::limelightDrive() {
    return xboxController1->GetXButton();
}

/**
 * Determines whether to drive straight
 * 
 * @author Dominic Rutkowski
 * @since 2-19-2019
 * 
 * @returns True if the robot should drive straight, false otherwise
 */
bool DoubleXboxController::straightDrive() {
    return xboxController1->GetYButton();
}

/**
 * Determines at what speed to drive the left motor group based on
 * the Y axis value of the first controller's left joystick
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double on [-1, 1] representing at what speed the left motors will drive
 */
double DoubleXboxController::drivetrainLeftSpeed() {
    double left1Y = -xboxController1->GetY(frc::Joystick::JoystickHand::kLeftHand);
    if (left1Y >= DRIVETRAIN_DEADZONE || left1Y <= -DRIVETRAIN_DEADZONE) {
        return left1Y;
    }
    return 0;
}

/**
 * Determines at what speed to drive the right motor group based on
 * the Y axis value of the first controller's right joystick
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double on [-1, 1] representing at what speed the right motors will drive
 */
double DoubleXboxController::drivetrainRightSpeed() {
    double right1Y = -xboxController1->GetY(frc::Joystick::JoystickHand::kRightHand);
    if (right1Y >= DRIVETRAIN_DEADZONE || right1Y <= -DRIVETRAIN_DEADZONE) {
        return right1Y;
    }
    return 0;
}

/**
 * Determines whether to open the claw based on if the first controller's 
 * right trigger is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should open, false otherwise
 */
bool DoubleXboxController::openClaw() {
    return xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3;
}

/**
 * Determines whether to close the claw based on if the first controller's 
 * left trigger is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should close, false otherwise
 */
bool DoubleXboxController::closeClaw() {
    return xboxController1->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

/**
 * Determines whether to change to low gear based on if the first controller's
 * left bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the robot should switch to low gear, false otherwise
 */
bool DoubleXboxController::setLowGear() {
    return xboxController1->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

/**
 * Determines whether to change to high gear based on if the first controller's
 * right bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the robot should switch to high gear, false otherwise
 */
bool DoubleXboxController::setHighGear() {
    return xboxController1->GetBumper(frc::Joystick::JoystickHand::kRightHand);
}

/**
 * Determines whether to raise the claw based on if the first controller's
 * A button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should be raised, false otherwise
 */
bool DoubleXboxController::raiseClaw() {
    return xboxController1->GetAButton();
}

/**
 * Determines whether to raise the claw based on if the first controller's
 * B button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should be lowered, false otherwise
 */
bool DoubleXboxController::lowerClaw() {
    return xboxController1->GetBButton();
}

/**
 * Determines whether to hold the elevator at
 * its current level
 * 
 * @author Dominic Rutkowsi
 * @since 3-15-2019
 * 
 * @returns True if the robot should hold its elevator, false otherwise
 */
bool DoubleXboxController::holdElevator() {
    return xboxController2->GetStickButton(frc::Joystick::JoystickHand::kLeftHand);
}

/**
 * Determines what speed to operate the elevator at based on the
 * Y axis value of the second controller's right joystick
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double on [-1, 1] representing what speed the elevator should drive at
 */
double DoubleXboxController::elevatorSpeed() {
    double right2Y = xboxController2->GetY(frc::Joystick::JoystickHand::kRightHand);
    if(right2Y >= ELEVATOR_DEADZONE || right2Y <= -ELEVATOR_DEADZONE) {
        return right2Y;
    }
    return 0;
}

/**
 * Determines whether to eject cargo based on if the second controller's
 * left bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the front cargo out should run, false otherwise
 */
bool DoubleXboxController::ejectCargo() {
    return xboxController2->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3;;
}

/**
 * Determines whether to run the cargo intake based on if the second controller's
 * left trigger is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the cargo intake should run, false otherwise
 */
bool DoubleXboxController::runIntake() {
    return xboxController2->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

/**
 * Determines whether to run the cargo intake in reverse based on if the second controller's
 * left bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 3-15-2019
 * 
 * @returns True if the cargo intake should run in reverse, false otherwise
 */
bool DoubleXboxController::runIntakeReverse() {
    return xboxController2->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

/**
 * Determines whether to set the Limelight to vision mode based on if the first
 * controller's start button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the Limelight should be switched to vision mode, false otherwise
 */
bool DoubleXboxController::setLimelightVisionMode() {
    return xboxController1->GetStartButton();
}

/**
 * Determines whether to set the Limelight to camera mode based on if the first
 * controller's back button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the Limelight should be switched to camera mode, false otherwise
 */
bool DoubleXboxController::setLimelightCameraMode() {
    return xboxController1->GetBackButton();
}
