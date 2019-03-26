#ifndef DRIVE_BASE_H
#define DRIVE_BASE_H

#include "RobotMap.h"

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class DriveBase {
private:
    // Left motor controllers
    TalonSRX *leftTalon1;
    TalonSRX *leftTalon2;
    TalonSRX *leftTalon3;

    // Right motor controllers
    TalonSRX *rightTalon1;
    TalonSRX *rightTalon2;
    TalonSRX *rightTalon3;

    // NavX
    AHRS *navx;
    double navxInitValue;

    // Limelight
    std::shared_ptr<NetworkTable> limelightNetworkTable;

    // Gear shifting solenoid
    frc::Solenoid *lowGearSolenoid;
    frc::Solenoid *highGearSolenoid;
    
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

    bool driveToReflection(double speed);
    bool teleopDriveToReflection(double speed);
    bool teleopLimelightDrive(double speed);
    bool alignedWithTarget = false;

    const double LEFT_ENCODER_TICKS_PER_INCH = 116.711067093;
    const double RIGHT_ENCODER_TICKS_PER_INCH = 117.837349601;

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
    
    bool getIsInHighGear();
};

#endif