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
    } catch (std::exception &exception) {
        std::string error = "Error instantiating navX MXP:  ";
        error += exception.what();
        DriverStation::ReportError(error.c_str());
    }

    // Limelight
    limelightNetworkTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    // Gear shifting solenoids
    lowGearSolenoid = new frc::Solenoid(LOW_GEAR_SOLENOID);
    highGearSolenoid = new frc::Solenoid(HIGH_GEAR_SOLENOID);

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

    // Gear shifting solenoids
    delete lowGearSolenoid;
    delete highGearSolenoid;

    // Drivetrain encoders
    delete leftEncoder;
    delete rightEncoder;
}