#include "Controls/SingleXboxController.h"

SingleXboxController::SingleXboxController() {
    xboxController = new frc::XboxController(0);
}

SingleXboxController::~SingleXboxController() {
    delete xboxController;
}

/**
 * Determines at what speed to drive the left motor group based on
 * the Y axis value of left joystick
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double on [-1, 1] representing at what speed the left motors will drive
 */
double SingleXboxController::getDrivetrainLeftSpeed() {
    double leftY = -xboxController->GetY(frc::Joystick::JoystickHand::kLeftHand);
    if (leftY >= DRIVETRAIN_DEADZONE || leftY <= -DRIVETRAIN_DEADZONE) {
        return leftY;
    }
    return 0;
}

/**
 * Determines at what speed to drive the right motor group based on
 * the Y axis value of the right joystick
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double on [-1, 1] representing at what speed the right motors will drive
 */
double SingleXboxController::getDrivetrainRightSpeed() {
    double rightY = -xboxController->GetY(frc::Joystick::JoystickHand::kRightHand);
    if (rightY >= DRIVETRAIN_DEADZONE || rightY <= DRIVETRAIN_DEADZONE) {
        return rightY;
    }
    return 0;
}

/**
 * Determines whether to open the claw based on if the
 * right trigger is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should open, false otherwise
 */
bool SingleXboxController::getOpenClaw() {
    return xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kRightHand) > 0.3;
}

/**
 * Determines whether to close the claw based on if the
 * left trigger is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should close, false otherwise
 */
bool SingleXboxController::getCloseClaw() {
    return xboxController->GetTriggerAxis(frc::Joystick::JoystickHand::kLeftHand) > 0.3;
}

/**
 * Determines whether to change to high gear based on if the
 * right bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the robot should switch to high gear, false otherwise
 */
bool SingleXboxController::getSetHighGear() {
    return xboxController->GetBumper(frc::Joystick::JoystickHand::kRightHand);
}

/**
 * Determines whether to change to low gear based on if the
 * left bumper is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the robot should switch to low gear, false otherwise
 */
bool SingleXboxController::getSetLowGear() {
    return xboxController->GetBumper(frc::Joystick::JoystickHand::kLeftHand);
}

/**
 * Determines whether to raise the claw based on if the
 * A button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should be raised, false otherwise
 */
bool SingleXboxController::getRaiseClaw() {
    return xboxController->GetAButton();
}

/**
 * Determines whether to raise the claw based on if the
 * B button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the claw should be lowered, false otherwise
 */
bool SingleXboxController::getLowerClaw() {
    return xboxController->GetBButton();
}

/**
 * Determines whether to operate the elevator at based on if the
 * X and Y buttons are pressed
 * X button = raise elevator
 * Y button = lower elevator
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns A double in {-1, 0, 1} representing whether to lower the elevator (-1),
 *          leave the elevator still (0), or raise the elevator (1)
 */
double SingleXboxController::getElevatorSpeed() {
    if (xboxController->GetXButton()) {
        return 1;
    }
    if (xboxController->GetYButton()) {
        return -1;
    }
    return 0;
}

/**
 * Determines whether to run the front cargo out based on if
 * left joystick is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the front cargo out should run, false otherwise
 */
bool SingleXboxController::getRunFrontOut() {
    return xboxController->GetStickButton(frc::Joystick::JoystickHand::kLeftHand);
}

/**
 * Determines whether to run the back cargo out based on if the
 * right joystick is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the back cargo out should run, false otherwise
 */
bool SingleXboxController::getRunBackOut() {
    return xboxController->GetStickButton(frc::Joystick::JoystickHand::kRightHand);
}

/**
 * Determines whether to run the cargo intake based on if the 
 * start button is pressed
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns True if the cargo intake should run, false otherwise
 */
bool SingleXboxController::getRunIntake() {
    return xboxController->GetStartButton();
}

/**
 * Determines not to set the Limelight to vision mode
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns False since the single controller does not support multiple Limelight modes
 */
bool SingleXboxController::getSetLimelightVision() {
    return false;
}

/**
 * Determines not to set the Limelight to camera mode
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @returns False since the single controller does not support multiple Limelight modes
 */
bool SingleXboxController::getSetLimelightCamera() {
    return false;
}