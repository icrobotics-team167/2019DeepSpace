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

    updateLimelight();

    // Gear shifting solenoid
    lowGearSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, LOW_GEAR_SOLENOID);
    highGearSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, HIGH_GEAR_SOLENOID);

    // Drivetrain encoders
    leftEncoder = new frc::Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B, true);
    rightEncoder = new frc::Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);

    // Current gear
    bool isInHighGear;
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
    delete lowGearSolenoid;
    delete highGearSolenoid;

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
    // low gear fudge factor
    if (inches > 5) {
        inches -= 2.3;
    }
    
    double rotationAngle = navx->GetAngle();
    
    SmartDashboard::PutNumber("Rotation angle: ", rotationAngle);
    SmartDashboard::PutNumber("Heading: ", navxInitValue);
    
    //update error calcualtions for control system
    double headingError = navxInitValue - rotationAngle;
    double diffError = headingError - straightDrivePreviousError;   
    
    SmartDashboard::PutNumber("Heading error: ", headingError);
    SmartDashboard::PutNumber("Differential error: ", diffError);

    //calculate left and right speeds for drive base heading correction
    double leftSpeed = speed + (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);
    double rightSpeed = speed - (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);

    SmartDashboard::PutNumber("Total error: ", straightDriveTotalError);
    SmartDashboard::PutNumber("Left speed: ", leftSpeed);
    SmartDashboard::PutNumber("Right speed: ", rightSpeed);

    //set max/min limits on adjusted speed values
    if (rightSpeed > 1) {
        rightSpeed = 1;
    }
    if (rightSpeed < -1) {
        rightSpeed = -1;
    }
    if (leftSpeed > 1) {
        leftSpeed = 1;
    }
    if (leftSpeed < -1) {
        leftSpeed = -1;
    }
    // target reached, reset encoders and stop motors
    if (abs(leftEncoder->Get()) > LEFT_ENCODER_TICKS_PER_INCH * inches &&
        abs(rightEncoder->Get()) > RIGHT_ENCODER_TICKS_PER_INCH * inches) {
        straightDrivePreviousError = 0;
        straightDriveTotalError = 0;
        drive(0, 0);
        return true;
    }
 
    drive(leftSpeed, rightSpeed);

    straightDrivePreviousError = headingError;
    straightDriveTotalError += headingError;

    return false;
}

//drive to heading
bool DriveBase::driveHeading(double inches, double avgSpd, double targetHeading, double arc)
{
    //low gear fudge factor
    if (inches > 5) 
    {
        inches -= 2.3;
    }

    double currentHeading = navx->GetAngle();
    
    SmartDashboard::PutNumber("CurrentHeading: ", currentHeading);
    SmartDashboard::PutNumber("TargetHeading: ", targetHeading);
    
    //update error calcualtions for control system
    double headingError = targetHeading - currentHeading;
    double diffError = headingError - straightDrivePreviousError;   
    
    SmartDashboard::PutNumber("Heading error: ", headingError);
    SmartDashboard::PutNumber("Differential error: ", diffError);

    //calculate left and right speeds for drive base heading correction
    double leftSpeed = avgSpd + (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);
    double rightSpeed = avgSpd - (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);

    SmartDashboard::PutNumber("Total error: ", straightDriveTotalError);
    SmartDashboard::PutNumber("Left speed: ", leftSpeed);
    SmartDashboard::PutNumber("Right speed: ", rightSpeed);

    //set max/min limits on adjusted speed values
    if (rightSpeed > 1) {
        rightSpeed = 1;
    }
    if (rightSpeed < -1) {
        rightSpeed = -1;
    }
    if (leftSpeed > 1) {
        leftSpeed = 1;
    }
    if (leftSpeed < -1) {
        leftSpeed = -1;
    }
    // target reached, reset encoders and stop motors
    if (abs(leftEncoder->Get()) > LEFT_ENCODER_TICKS_PER_INCH * inches &&
        abs(rightEncoder->Get()) > RIGHT_ENCODER_TICKS_PER_INCH * inches) {
        straightDrivePreviousError = 0;
        straightDriveTotalError = 0;
        drive(0, 0);
        return true;
    }
 
    drive(leftSpeed, rightSpeed);

    straightDrivePreviousError = headingError;
    straightDriveTotalError += headingError;

    return false;

}

void DriveBase::teleopStraightDrive(double speed) {
    double rotationAngle = navx->GetAngle();
    
    double headingError = navxInitValue - rotationAngle;
    double diffError = headingError - straightDrivePreviousError;   
    
    double leftSpeed = speed + (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);
    double rightSpeed = speed - (straightDriveKP * headingError + straightDriveKI * straightDriveTotalError + straightDriveKD * diffError);

   if (rightSpeed > 1) {
        rightSpeed = 1;
    }
    if (rightSpeed < -1) {
        rightSpeed = -1;
    }
    if (leftSpeed > 1) {
        leftSpeed = 1;
    }
    if (leftSpeed < -1) {
        leftSpeed = -1;
    }

    drive(leftSpeed, rightSpeed);

    straightDrivePreviousError = headingError;
    straightDriveTotalError += headingError;
}

void DriveBase::resetPID() {
    straightDrivePreviousError = 0;
    straightDriveTotalError = 0;
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
    if (abs(navx->GetAngle() - navxInitValue) < abs(angle)) {
        if (angle >= 0) {
            drive(speed, -speed);
        } else {
            drive(-speed, speed);
        }
        return false;
    }
    drive(0, 0);
    return true;
}

/**
 * Drives to the reflective tape
 * 
 * @author Dominic Rutkowski
 * @author Vladimir Tivanski
 * @since 2-15-2019
 * 
 * @param speed The speed at which the robot will drive
 * 
 * @returns True if the drive is complete, false otherwise
 */
bool DriveBase::driveToReflection(double speed) {
    setLimelightVision();

    double tx = getLimelightTx();
    double ty = getLimelightTy();
    double ta = getLimelightTa();
    double ts = getLimelightTs();
    double tv = getLimelightTv();

    if (tv > 0) {
        if (ta >= limelightTargetArea) {
            return true;
        }
        double turn = tx * limelightSteerK;
        double drive = (limelightTargetArea - ta) * speed + 0.1;
        double leftSpeed = drive + turn;
        double rightSpeed = drive - turn;
        if (leftSpeed > limelightMaxDriveSpeed) {
            leftSpeed = limelightMaxDriveSpeed;
        }
        if (leftSpeed < -limelightMaxDriveSpeed) {
            leftSpeed = -limelightMaxDriveSpeed;
        }
        if (rightSpeed > limelightMaxDriveSpeed) {
            rightSpeed = limelightMaxDriveSpeed;
        }
        if (rightSpeed < -limelightMaxDriveSpeed) {
            rightSpeed = -limelightMaxDriveSpeed;
        }
        if (ta > 1.5) {
            setLowGear();
        }
        DriveBase::drive(leftSpeed, rightSpeed);
        return false;
    } else {
        drive(0, 0);
        return true;
    }
}

/**
 * This method will first align the robot within 1 degree of the center of the vision tape.
 * Then it will use the limelight to drive the rest of the way there.
 * 
 * This is intended to minimalize the error when driving to a reflection
 * 
 * @param speed The speed at which the robot will drive at
 * 
 * @author Vladimir Tivanski
 * @since 3-11-2019
 * 
 * @returns A bool containing whether or not the robot has successfully driven to the tape
 */ 
bool DriveBase::teleopDriveToReflection(double speed) {
    double tx = getLimelightTx();

    if ((tx > 1 || tx < -1) && !alignedWithTarget) {
        pointTurn(tx, .5);
        return false;
    } else {
        alignedWithTarget = true;
        return teleopLimelightDrive(speed);
    }
}

bool DriveBase::teleopLimelightDrive(double speed) {
    setLimelightVision();

    double tx = getLimelightTx();
    double ty = getLimelightTy();
    double ta = getLimelightTa();
    double ts = getLimelightTs();
    double tv = getLimelightTv();

    if (tv > 0) {
        if (ta >= limelightTargetArea) {
            alignedWithTarget = false;
            return true;
        }
        double turn = tx * limelightSteerK;
        double drive = (limelightTargetArea - ta) * speed;
        double leftSpeed = drive + turn;
        double rightSpeed = drive - turn;
        if (leftSpeed > limelightMaxDriveSpeed) {
            leftSpeed = limelightMaxDriveSpeed;
        }
        if (leftSpeed < -limelightMaxDriveSpeed) {
            leftSpeed = -limelightMaxDriveSpeed;
        }
        if (rightSpeed > limelightMaxDriveSpeed) {
            rightSpeed = limelightMaxDriveSpeed;
        }
        if (rightSpeed < -limelightMaxDriveSpeed) {
            rightSpeed = -limelightMaxDriveSpeed;
        }
        DriveBase::drive(leftSpeed, rightSpeed);
        return false;
    } else {
        drive(0, 0);
        alignedWithTarget = false;
        return true;
    }
}

/**
 * Sets the gearbox to low gear
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void DriveBase::setLowGear() {
    lowGearSolenoid->Set(true);
    highGearSolenoid->Set(false);
    isInHighGear = false;
}

/**
 * Sets the gearbox to high gear
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void DriveBase::setHighGear() {
    lowGearSolenoid->Set(false);
    highGearSolenoid->Set(true);
    isInHighGear = true;
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

/**
 * Updates the Limelight vision values
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */
void DriveBase::updateLimelight() {
    limelightNetworkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    limelightNetworkTable->PutNumber("ledMode", limelightVision ? 3 : 1);
    limelightNetworkTable->PutNumber("camMode", limelightVision ? 0 : 1);
}

double DriveBase::getLimelightTx() {
    return limelightNetworkTable->GetNumber("tx", 0.0);
}

double DriveBase::getLimelightTy() {
    return limelightNetworkTable->GetNumber("ty", 0.0);
}

double DriveBase::getLimelightTa() {
    return limelightNetworkTable->GetNumber("ta", 0.0);
}

double DriveBase::getLimelightTs() {
    return limelightNetworkTable->GetNumber("ts", 0.0);
}

double DriveBase::getLimelightTv() {
    return limelightNetworkTable->GetNumber("tv", 0.0);
}

void DriveBase::setLimelightVision() {
    limelightVision = true;
}

void DriveBase::setLimelightLeft() {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 1);
}

void DriveBase::setLimelightRight() {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 2);
}

void DriveBase::setLimelightLowest() {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
}

void DriveBase::setLimelightCamera() {
    limelightVision = false;
}

bool DriveBase::getIsInHighGear() {
    return isInHighGear;
}