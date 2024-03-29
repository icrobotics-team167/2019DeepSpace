#ifndef DRIVE_BASE_H
#define DRIVE_BASE_H

#include "RobotMap.h"

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <AHRS.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class DriveBase {
private:
    // Left motor controllers
    rev::CANSparkMax *leftSpark1;
    rev::CANSparkMax *leftSpark2;
    rev::CANSparkMax *leftSpark3;

    // Right motor controllers
    rev::CANSparkMax *rightSpark1;
    rev::CANSparkMax *rightSpark2;
    rev::CANSparkMax *rightSpark3;

    // NavX
    AHRS *navx;
    double navxInitValue;

    // Limelight
    std::shared_ptr<NetworkTable> limelightNetworkTable;

    // Gear shifting solenoid
    frc::Solenoid *gearShifterSolenoid;
    
    // Drivetrain encoders
    frc::Encoder *leftEncoder;
    frc::Encoder *rightEncoder;

    // Current gear
    bool isInHighGear;
public:
    DriveBase();
    ~DriveBase();

    void drive(double leftSpeed, double rightSpeed);

    bool straightDrive(double inches, double speed);
    bool driveHeading(double inches, double avgSpd, double heading, double arc = 1.0);
    void teleopStraightDrive(double speed);
    bool pointTurn(double angle, double speed);
    bool alignWithTarget();

    bool driveToReflection(double speed);
    bool teleopDriveToReflection(double speed);
    bool teleopLimelightDrive(double speed);
    bool alignedWithTarget = false;

    const double LEFT_ENCODER_TICKS_PER_INCH = 116.619420989;
    const double RIGHT_ENCODER_TICKS_PER_INCH = 116.193064549;

    const double straightDriveKP = 0.02;
    const double straightDriveKI = 0.0001;
    const double straightDriveKD = 0.01;
    double straightDrivePreviousError = 0;
    double straightDriveTotalError = 0;

    void resetPID();

    const double limelightSteerK = 0.04;
    const double limelightTargetArea = 3.5;
    const double limelightMaxDriveSpeed = 0.65;
    const double limelightMaxTurnSpeed = 1;

    frc::Encoder *getLeftEncoder();
    frc::Encoder *getRightEncoder();
    void resetEncoders();

    void setLowGear();
    void setHighGear();

    AHRS *getNavx();
    void updateNavx();

    void updateLimelight();
    double getLimelightTx();
    double getLimelightTy();
    double getLimelightTa();
    double getLimelightTs();
    double getLimelightTv();
    bool limelightVision = true;
    void setLimelightVision();
    void setLimelightCamera();

    void setLimelightLeft();
    void setLimelightRight();
    void setLimelightLowest();
    void setLimelightLowestHatchPickup();
    
    bool getIsInHighGear();
};

#endif