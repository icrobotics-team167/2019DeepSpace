/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
    autoChooser.SetDefaultOption(nullAuto, nullAuto);
    autoChooser.AddOption(leftBackRocket, leftBackRocket);
    autoChooser.AddOption(rightBackRocket, rightBackRocket);
    autoChooser.AddOption(leftCargoShip, leftCargoShip);
    autoChooser.AddOption(rightCargoShip, rightCargoShip);
    SmartDashboard::PutData("Auto Modes", &autoChooser);

    driveBase = new DriveBase();
    claw = new Claw();
    elevator = new Elevator();
    bling = new Bling();
    cargo = new Cargo();

    controller = new DoubleXboxController();

    teleop = new Teleop(driveBase, claw, elevator, bling, cargo, controller);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
    driveBase->updateLimelight();
    SmartDashboard::PutNumber("Left encoder: ", driveBase->getLeftEncoder()->Get());
    SmartDashboard::PutNumber("Right encoder: ", driveBase->getRightEncoder()->Get());
    SmartDashboard::PutNumber("Limelight tx: ", driveBase->getLimelightTx());
    SmartDashboard::PutNumber("Limelight ty: ", driveBase->getLimelightTy());
    SmartDashboard::PutNumber("Limelight ta: ", driveBase->getLimelightTa());
    SmartDashboard::PutNumber("Limelight ts: ", driveBase->getLimelightTs());
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
    selectedAuto = autoChooser.GetSelected();
    selectedAuto = SmartDashboard::GetString("Auto Selector", nullAuto);
    std::cout << "Auto selected: " << selectedAuto << std::endl;

    driveBase->setLimelightVision();

    // if (selectedAuto == leftBackRocket) {
    //     autoRoutine = new LeftBackRocket(driveBase, claw, elevator, bling, cargo, teleop);
    // } else if (selectedAuto == rightBackRocket) {
    //     autoRoutine = new RightBackRocket(driveBase, claw, elevator, bling, cargo, teleop);
    // } else if (selectedAuto == leftCargoShip) {
    //     autoRoutine = new LeftCargoShip(driveBase, claw, elevator, bling, cargo, teleop);
    // } else if (selectedAuto == rightCargoShip) {
    //     autoRoutine = new RightCargoShip(driveBase, claw, elevator, bling, cargo, teleop);
    // } else {
    //     autoRoutine = new NullAuto(driveBase, claw, elevator, bling, cargo, teleop);
    // }
    autoRoutine = new RightBackRocket(driveBase, claw, elevator, bling, cargo, controller, teleop);
}

void Robot::AutonomousPeriodic() {
    autoRoutine->run();
}

void Robot::TeleopInit() {
    teleop->init();
}

void Robot::TeleopPeriodic() {
    teleop->periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
