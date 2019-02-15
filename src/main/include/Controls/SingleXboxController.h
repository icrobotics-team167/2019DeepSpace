#ifndef SINGLE_XBOX_CONTROLLER_H
#define SINGLE_XBOX_CONTROLLER_H

#include "Controls/GenericController.h"
#include <frc/WPILib.h>

class SingleXboxController : public GenericController {
private:
    frc::XboxController *xboxController;
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
    bool getRaiseElevator() override;
    bool getLowerElevator() override;
    bool getRunFrontOut() override;
    bool getRunBackOut() override;
    bool getRunIntake() override;
};

#endif