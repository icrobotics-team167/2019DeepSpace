/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Subsystems/DriveBase.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Bling.h"
#include "Subsystems/Cargo.h"

#include "Auto/AutoRoutine.h"
#include "Auto/NullAuto.h"
#include "Auto/FrontRocket.h"
#include "Auto/LeftBackRocket.h"
#include "Auto/RightBackRocket.h"
#include "Auto/LeftCargoShip.h"
#include "Auto/RightCargoShip.h"

#include "Controls/GenericController.h"
#include "Controls/SingleXboxController.h"
#include "Controls/DoubleXboxController.h"

#include "Teleop.h"

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
private:
    frc::SendableChooser<std::string> autoChooser;
    const std::string nullAuto = "Null Auto";
    const std::string leftBackRocket = "Left Back Rocket";
    const std::string rightBackRocket = "Right Back Rocket";
    const std::string leftCargoShip = "Left Cargo Ship";
    const std::string rightCargoShip = "Right Cargo Ship";
    std::string selectedAuto;

    DriveBase *driveBase;
    Claw *claw;
    Elevator *elevator;
    Bling *bling;
    Cargo *cargo;

    AutoRoutine *autoRoutine;

    GenericController *controller;

    Teleop *teleop;
};
