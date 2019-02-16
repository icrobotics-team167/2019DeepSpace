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
    double getDrivetrainLeftSpeed() override;
    double getDrivetrainRightSpeed() override;
    bool getOpenClaw() override;
    bool getCloseClaw() override;
    bool getSetHighGear() override;
    bool getSetLowGear() override;
    bool getRaiseClaw() override;
    bool getLowerClaw() override;
    bool getRaiseElevator() override;
    bool getLowerElevator() override;
    double getElevatorSpeed() override;
    bool getRunFrontOut() override;
    bool getRunBackOut() override;
    bool getRunIntake() override;
    bool getSetLimelightVision() override;
    bool getSetLimelightCamera() override;
};

#endif