#ifndef SINGLE_XBOX_CONTROLLER_H
#define SINGLE_XBOX_CONTROLLER_H

#include "Controls/GenericController.h"
#include <frc/WPILib.h>

class SingleXboxController : public GenericController {
private:
    frc::XboxController *xboxController;
    const double DRIVETRAIN_DEADZONE = 0.07;
public:
    SingleXboxController();
    ~SingleXboxController();
    double getDrivetrainLeftSpeed() override;
    double getDrivetrainRightSpeed() override;
    bool getOpenClaw() override;
    bool getCloseClaw() override;
    bool getSetHighGear() override;
    bool getSetLowGear() override;
    bool getRaiseClaw() override;
    bool getLowerClaw() override;
    double getElevatorSpeed() override;
    bool getRunFrontOut() override;
    bool getRunIntake() override;
    bool getSetLimelightVision() override;
    bool getSetLimelightCamera() override;
    bool getDriveWithLimelight() override;
    bool getDriveStraight() override;
    bool getReverseIntake() override;

};

#endif