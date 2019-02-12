#include "Subsystems/DriveBase.h"

DriveBase::DriveBase() {
    // Left motor controllers
    leftTalon1 = new TalonSRX(LEFT_TALON_1);
    leftTalon2 = new TalonSRX(LEFT_TALON_2);
    leftTalon3 = new TalonSRX(LEFT_TALON_3);

    // Right motor controllers
    rightTalon1 = new TalonSRX(RIGHT_TALON_1);
    rightTalon2 = new TalonSRX(RIGHT_TALON_2);
    rightTalon3 = new TalonSRX(RIGHT_TALON_3);

    // NavX
    try {
        navx = new AHRS(SPI::Port::kMXP);
        navxInitValue = navx->GetAngle();
    } catch (std::exception &exception) {
        std::string error = "Error instantiating navX MXP:  ";
        error += exception.what();
        DriverStation::ReportError(error.c_str());
    }

    // Limelight
    limelightNetworkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    // Gear shifting solenoid
    gearShifterSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, GEAR_SHIFTER_SOLENOID);

    // Drivetrain encoders
    leftEncoder = new frc::Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B, false);
    rightEncoder = new frc::Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);
}

DriveBase::~DriveBase() {
    // Left motor controllers
    delete leftTalon1;
    delete leftTalon2;
    delete leftTalon3;

    // Right motor controllers
    delete rightTalon1;
    delete rightTalon2;
    delete rightTalon3;

    // NavX
    delete navx;

    // Limelight
    // Automatically deallocated since the limelight is a smart_ptr

    // Gear shifting solenoid
    delete gearShifterSolenoid;

    // Drivetrain encoders
    delete leftEncoder;
    delete rightEncoder;
}

/**
 * Sets the speeds on each side of the robot.
 * 
 * @author Vladimir Tivanski
 * @since 2-11-2019
 * 
 * @param leftSpeed The speed that the left motor group will drive at
 * @param rightSpeed The speed that the right motor group will drive at
 */ 
void DriveBase::drive(double leftSpeed, double rightSpeed) {
    leftSpeed *= -1;

    leftTalon1->Set(ControlMode::PercentOutput, leftSpeed);
    leftTalon2->Set(ControlMode::PercentOutput, leftSpeed);
    leftTalon3->Set(ControlMode::PercentOutput, leftSpeed);

    rightTalon1->Set(ControlMode::PercentOutput, rightSpeed);
    rightTalon2->Set(ControlMode::PercentOutput, rightSpeed);
    rightTalon3->Set(ControlMode::PercentOutput, rightSpeed);
}

/**
 * Drives straigt by adjusting the speeds so that the robot will 
 * realign itself if it drives slightly off track.
 * 
 * @author Vladimir Tivanski
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @param inches The number of inches that the robot is to drive
 * @param speed The speed that both motor groups will drive at
 * 
 * @returns True if the drive is complete, false otherwise
 */ 
bool DriveBase::straightDrive(double inches, double speed) {
    double rotationAngle = navx->GetAngle();
    
    SmartDashboard::PutNumber("rotation angle", rotationAngle);
    SmartDashboard::PutNumber("Heading", navxInitValue);

    double headingError = navxInitValue - rotationAngle;
    double diffError = headingError - previousError;   
    
    SmartDashboard::PutNumber("Heading Error", headingError);
    SmartDashboard::PutNumber("diff Error", diffError);

    double leftSpeed = speed + (KP * headingError + KI * totalError + KD * diffError);
    double rightSpeed = speed - (KP * headingError + KI * totalError + KD * diffError);


    SmartDashboard::PutNumber("Total Error", totalError);
    SmartDashboard::PutNumber("Left Speed", leftSpeed);
    SmartDashboard::PutNumber("Right Speed", rightSpeed);

    if (rightSpeed > 1) {
        rightSpeed = 1;
    }

    if (leftSpeed > 1) {
        leftSpeed = 1;
    }

    if (leftEncoder->Get() > LEFT_ENCODER_TICKS_PER_INCH * inches &&
        rightEncoder->Get() > RIGHT_ENCODER_TICKS_PER_INCH * inches) {
        return true;
    }

    drive(leftSpeed, rightSpeed);

    previousError = headingError;
    totalError += headingError;

    return false;
}

/**
 * Standard implementation of a point turn
 * 
 * @author Vladimir Tivanski
 * @author Dominic Rutkowski
 * @since 2-11-2019
 * 
 * @param angle The angle to turn (positive is clockwise, negative is counterclockwise)
 * @param speed The speed at which the robot will turn
 * 
 * @returns True if the turn is complete, false otherwise
 */
bool DriveBase::pointTurn(double angle, double speed) {
    if (abs(navx->GetAngle() - navxInitValue) < angle) {
        if (angle >= 0) {
            drive(speed, -speed);
        } else {
            drive(-speed, speed);
        }
        return false;
    }
    return true;
}

/**
 * Sets the gearbox to low gear
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void DriveBase::setLowGear() {
    gearShifterSolenoid->Set(false);
}

/**
 * Sets the gearbox to high gear
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void DriveBase::setHighGear() {
    gearShifterSolenoid->Set(true);
}

/**
 * Gets the left encoder
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the left encoder
 */ 
frc::Encoder *DriveBase::getLeftEncoder() {
    return leftEncoder;
}

/**
 * Gets the right encoder
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the right encoder
 */ 
frc::Encoder *DriveBase::getRightEncoder() {
    return rightEncoder;
}

/**
 * Resets the value of each encoder to 0
 * 
 * @author Dominic Rutkowski
 * @since 2-11-2019
 */
void DriveBase::resetEncoders() {
    leftEncoder->Reset();
    rightEncoder->Reset();
}

/**
 * Gets the NavX
 * 
 * @author Dominic Rutkowski
 * @author Vladimir Tivanski
 * @since 2-10-2019
 * 
 * @returns A pointer to the navX 
 */
AHRS *DriveBase::getNavx() {
    return navx;
}

/**
 * Updates naxvInitValue to the current bearing
 * 
 * @author Dominic Rutkowski
 * @since 2-11-2019
 */
void DriveBase::updateNavx() {
    navxInitValue = navx->GetAngle();
}