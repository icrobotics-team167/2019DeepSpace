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
    m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
    SmartDashboard::PutData("Auto Modes", &m_chooser);

    driveBase = new DriveBase();
    claw = new Claw();
    elevator = new Elevator();
    bling = new Bling();
    cargo = new Cargo();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

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
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //     kAutoNameDefault);
    std::cout << "Auto selected: " << m_autoSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
    }

    autoRoutine = new AutoTest(driveBase, claw, elevator, bling, cargo);
}

void Robot::AutonomousPeriodic() {
    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
    }

    autoRoutine->run();
}

void Robot::TeleopInit() {
    controller = new frc::XboxController(0);
    
}

void Robot::TeleopPeriodic() {
    //Joysticks
    // These values are reversed for some reason
    double leftY = -controller->GetY(Joystick::JoystickHand::kLeftHand);
    double rightY = -controller->GetY(Joystick::JoystickHand::kRightHand);
    driveBase->drive(leftY, rightY);
    driveBase->updateNavx();
    
    // Triggers
    if (controller->GetTriggerAxis(Joystick::JoystickHand::kLeftHand) > 0.3) {
        claw->closeClaw();
    }
    if (controller->GetTriggerAxis(Joystick::JoystickHand::kRightHand) > 0.3) {
        claw->openClaw();
    }

    // Bumpers
    if (controller->GetBumper(Joystick::JoystickHand::kLeftHand)) {
        driveBase->setLowGear();
    }
    if (controller->GetBumper(Joystick::JoystickHand::kRightHand)) {
        driveBase->setHighGear();
    }

    // A Button
    if (controller->GetAButton()) {
        claw->moveClawUp();
    }

    // B Button
    if (controller->GetBButton()) {
        claw->moveClawDown();
    }

    // X Button
    if (controller->GetXButton()) {
        elevator->raiseElevator(1);
    }
    else {
        elevator->stopElevator();
    }

    // Y Button
    if (controller->GetYButton()) {
        elevator->lowerElevator(1); 
    }
    else {
        elevator->stopElevator();
    }

    // Stick Buttons
    if (controller->GetStickButton(Joystick::JoystickHand::kLeftHand)) {
        cargo->runFrontOut(1);
    }
    else {
        cargo->stopFrontOut();
    }
    if (controller->GetStickButton(Joystick::JoystickHand::kRightHand)) {
        cargo->runBackOut(1);
    }
    else {
        cargo->stopBackOut();
    }

    // Start Button
    if (controller->GetStartButton()) {
        cargo->runIntake(1);
    }
    else {
        cargo->stopIntake();
    }
}

void Robot::TestPeriodic() {}

/**
 * Gets the DriveBase
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the DriveBase
 */ 
DriveBase *Robot::getDriveBase() {
    return driveBase;
}

/**
 * Gets the Claw
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the Claw
 */ 
Claw *Robot::getClaw() {
    return claw;
}

/**
 * Gets the Elevator
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the Elevator
 */ 
Elevator *Robot::getElevator() {
    return elevator;
}

/**
 * Gets the Bling
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the Bling
 */ 
Bling *Robot::getBling() {
    return bling;
}

/**
 * Gets the Cargo
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @returns A pointer to the Cargo
 */ 
Cargo *Robot::getCargo() {
    return cargo;
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
