#ifndef GENERIC_CONTROLLER_H
#define GENERIC_CONTROLLER_H

class GenericController {
protected:
    const double DRIVETRAIN_DEADZONE = 0.07;
    const double ELEVATOR_DEADZONE = 0.3;
public:
    virtual bool limelightDrive() = 0;
    virtual bool straightDrive() = 0;
    virtual double drivetrainLeftSpeed() = 0;
    virtual double drivetrainRightSpeed() = 0;

    virtual bool openClaw() = 0;
    virtual bool closeClaw() = 0;

    virtual bool setLowGear() = 0;
    virtual bool setHighGear() = 0;

    virtual bool raiseClaw() = 0;
    virtual bool lowerClaw() = 0;

    virtual bool holdElevator() = 0;
    virtual double elevatorSpeed() = 0;

    virtual bool ejectCargo() = 0;
    virtual bool runIntake() = 0;
    virtual bool runIntakeReverse() = 0;

    virtual bool setLimelightVisionMode() = 0;
    virtual bool setLimelightCameraMode() = 0;

    virtual bool sandstormAutoOverride() = 0;
};

#endif