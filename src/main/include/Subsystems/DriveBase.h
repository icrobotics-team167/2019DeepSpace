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

    // Gear shifting solenoids
    frc::Solenoid *lowGearSolenoid;
    frc::Solenoid *highGearSolenoid;
    
    // Drivetrain encoders
    frc::Encoder *leftEncoder;
    frc::Encoder *rightEncoder;
public:
    DriveBase();
    ~DriveBase();

    void drive(double leftSpeed, double rightSpeed);
    void tankDrive(double leftSpeed, double rightSpeed);
    void straightDrive(double speed);

    const double INCH_TO_LEFT_ENCODER = 120.23;
    const double INCH_TO_RIGHT_ENCODER = 121.38;

    double previousError = 0;
    double totalError = 0;

    const double KP = 0.02;
    const double KI = 0.0001;
    const double KD = 0.01;

    frc::Encoder *getLeftEncoder();
    frc::Encoder *getRightEncoder();
};

#endif