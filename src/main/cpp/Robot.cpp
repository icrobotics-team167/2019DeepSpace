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
void Robot::RobotPeriodic() {
    driveBase->updateLimelight();
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
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //     kAutoNameDefault);
    std::cout << "Auto selected: " << m_autoSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
    }

    driveBase->setLimelightVision();
    autoRoutine = new BackRocket(driveBase, claw, elevator, bling, cargo);
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
    controller = new DoubleXboxController();
    driveBase->setLimelightCamera();
    driveBase->setHighGear();
    bling->RunLeftLEDStrip(0.77); // green
    bling->RunRightLEDStrip(0.77);
    claw->moveClawDown();
    Wait(0.5);
    claw->openClaw();
}

void Robot::TeleopPeriodic() {
    // Driving
    double leftY = controller->getDrivetrainLeftSpeed();
    double rightY = controller->getDrivetrainRightSpeed();
    
    if (controller->getDriveWithLimelight()) {
        driveBase->teleopDriveToReflection(0.2);
    } else if (controller->getDriveStraight()) {
        driveBase->teleopStraightDrive(rightY == 0 ? 0.35 : rightY);
        driveBase->resetEncoders();
    } else if (controller->getDriveStraightReverse()) {
        driveBase->teleopStraightDrive(rightY == 0 ? -0.35 : rightY);
        driveBase->resetEncoders();
    } else {
        driveBase->resetPID();
        driveBase->drive(leftY, rightY);
    }

    driveBase->updateNavx();
    
    // Open and close claw
    if (controller->getCloseClaw()) {
        claw->closeClaw();
    } else if (controller->getOpenClaw()) {
        claw->openClaw();
    }

    // Gear shifting
    if (controller->getSetLowGear()) {
        driveBase->setLowGear();
        bling->RunLeftLEDStrip(0.69); // yellow
        bling->RunRightLEDStrip(0.69); 
    } else if (controller->getSetHighGear()) {
        driveBase->setHighGear();
        bling->RunLeftLEDStrip(0.77); // green
        bling->RunRightLEDStrip(0.77);
    }

    // Claw raising and lowering
    if (controller->getRaiseClaw()) {
        claw->moveClawUp();
    } else if (controller->getLowerClaw()) {
        claw->moveClawDown();
    }

    elevator->raiseElevator(controller->getElevatorSpeed());

    // Cargo out
    if (controller->getRunFrontOut()) {
        cargo->ejectCargo();
    } else if (controller->getRunBackOut()) {
        cargo->holdCargo();
    } else if (controller->getRunIntake()) {
        cargo->runIntake(1);
        cargo->holdCargo();
    } else {
        cargo->stopFront();
        cargo->stopBack();
        cargo->stopIntake();
    }
    
    if (controller->getSetLimelightVision()) {
        driveBase->setLimelightVision();
    } else if (controller->getSetLimelightCamera()) {
        driveBase->setLimelightCamera();
    }

    if (elevator->atMiddle()) {
        bling->RunLeftLEDStrip(0.61); // red
        bling->RunRightLEDStrip(0.61);
    }
    else if (driveBase->getIsInHighGear()) {
        bling->RunLeftLEDStrip(0.77); // green
        bling->RunRightLEDStrip(0.77);
    }
    else {
        bling->RunLeftLEDStrip(0.69); // yellow
        bling->RunRightLEDStrip(0.69);
    }

    SmartDashboard::PutNumber("Left encoder: ", driveBase->getLeftEncoder()->Get());
    SmartDashboard::PutNumber("Right encoder: ", driveBase->getRightEncoder()->Get()); 
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
