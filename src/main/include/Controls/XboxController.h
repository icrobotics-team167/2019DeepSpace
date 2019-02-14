#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class XboxController {
    private:
        frc::XboxController *wpiController;
    public:
        XboxController();
        ~XboxController();
        double getDrivetrainLeftSpeed();
        double getDrivetrainRightSpeed();
        bool getOpenClaw();
        bool getCloseClaw();
        bool getSetHighGear();
        bool getSetLowGear();
        bool getRaiseClaw();
        bool getLowerClaw();
        bool getRaiseElevator();
        bool getLowerElevator();
        bool getRunFrontOut();
        bool getRunBackOut();
        bool getRunIntake();
};

#endif