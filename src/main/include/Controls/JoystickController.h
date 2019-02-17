/*
#ifndef SINGLE_XBOX_CONTROLLER_H
#define SINGLE_XBOX_CONTROLLER_H

#include "Controls/GenericController.h"
#include <frc/WPILib.h>

class JoystickController : public GenericController {
private:
    frc::Joystick *leftJoystick;
    frc::Joystick *rightJoystick;
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
    double getElevatorSpeed() override;
    bool getRunFrontOut() override;
    bool getRunBackOut() override;
    bool getRunIntake() override;
};

#endif
*/