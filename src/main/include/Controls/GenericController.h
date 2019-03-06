#ifndef GENERIC_CONTROLLER_H
#define GENERIC_CONTROLLER_H

class GenericController {
private:
public:
    virtual double getDrivetrainLeftSpeed() = 0;
    virtual double getDrivetrainRightSpeed() = 0;
    virtual bool getOpenClaw() = 0;
    virtual bool getCloseClaw() = 0;
    virtual bool getSetHighGear() = 0;
    virtual bool getSetLowGear() = 0;
    virtual bool getRaiseClaw() = 0;
    virtual bool getLowerClaw() = 0;
    virtual double getElevatorSpeed() = 0;
    virtual bool getRunFrontOut() = 0;
    virtual bool getRunBackOut() = 0;
    virtual bool getRunIntake() = 0;
    virtual bool getSetLimelightVision() = 0;
    virtual bool getSetLimelightCamera() = 0;
    virtual bool getDriveWithLimelight() = 0;
    virtual bool getDriveStraight() = 0;
};

#endif