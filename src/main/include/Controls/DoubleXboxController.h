#ifndef DOUBLE_XBOX_CONTROLLER_H
#define DOUBLE_XBOX_CONTROLLER_H

#include "Controls/GenericController.h"
#include <frc/WPILib.h>

class DoubleXboxController : public GenericController {
private:
    frc::XboxController *xboxController1;
    frc::XboxController *xboxController2;
public:
    DoubleXboxController();
    ~DoubleXboxController();

    bool limelightDrive() override;
    bool straightDrive() override;
    double drivetrainLeftSpeed() override;
    double drivetrainRightSpeed() override;

    bool openClaw() override;
    bool closeClaw() override;

    bool setLowGear() override;
    bool setHighGear() override;

    bool raiseClaw() override;
    bool lowerClaw() override;

    bool holdElevator() override;
    double elevatorSpeed() override;

    bool ejectCargo() override;
    bool runIntake() override;
    bool runIntakeReverse() override;
    
    bool setLimelightVisionMode() override;
    bool setLimelightCameraMode() override;
};

#endif