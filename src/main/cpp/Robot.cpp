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
    //     autoRoutine = new LeftBackRocket(driveBase, claw, elevator, bling, cargo);
    // } else if (selectedAuto == rightBackRocket) {
    //     autoRoutine = new RightBackRocket(driveBase, claw, elevator, bling, cargo);
    // } else if (selectedAuto == leftCargoShip) {
    //     autoRoutine = new LeftCargoShip(driveBase, claw, elevator, bling, cargo);
    // } else if (selectedAuto == rightCargoShip) {
    //     autoRoutine = new RightCargoShip(driveBase, claw, elevator, bling, cargo);
    // } else {
    //     autoRoutine = new NullAuto(driveBase, claw, elevator, bling, cargo);
    // }
    autoRoutine = new RightBackRocket(driveBase, claw, elevator, bling, cargo, controller);
}

void Robot::AutonomousPeriodic() {
    autoRoutine->run();
}

void Robot::TeleopInit() {
    driveBase->setLimelightCamera();
    driveBase->setHighGear();
    bling->RunLeftLEDStrip(0.77); // green
    bling->RunRightLEDStrip(0.77);
    // claw->moveClawDown();
    driveBase->setHighGear();
    bling->RunLeftLEDStrip(0.77); // green
    bling->RunRightLEDStrip(0.77);
    // Wait(0.5);
    claw->openClaw();
}

void Robot::TeleopPeriodic() {
    // Driving
    double leftY = controller->drivetrainLeftSpeed();
    double rightY = controller->drivetrainRightSpeed();
    
    if (controller->limelightDrive()) {
        driveBase->teleopDriveToReflection(0.2);
    } else if (controller->straightDrive()) {
        driveBase->teleopStraightDrive(leftY);
        driveBase->resetEncoders();
    } else {
        driveBase->resetPID();
        driveBase->updateNavx();
        driveBase->drive(leftY, rightY);
    }
    
    // Open and close claw
    if (controller->closeClaw()) {
        claw->closeClaw();
        //bling->RunLEDStrip1(0);
        //bling->RunLEDStrip1(0);
    } else if (controller->openClaw()) {
        claw->openClaw();
        //bling->RunLEDStrip1(0);
        //bling->RunLEDStrip1(0);
    }

    // Gear shifting
    if (controller->setLowGear()) {
        driveBase->setLowGear();
        bling->RunLeftLEDStrip(0.69); // yellow
        bling->RunRightLEDStrip(0.69); 
    } else if (controller->setHighGear()) {
        driveBase->setHighGear();
        bling->RunLeftLEDStrip(0.77); // green
        bling->RunRightLEDStrip(0.77);
    }

    // Claw raising and lowering
    if (controller->raiseClaw()) {
        claw->moveClawUp();
        //bling->RunLEDStrip1(0);
        //bling->RunLEDStrip1(0);
    } else if (controller->lowerClaw()) {
        claw->moveClawDown();
        //bling->RunLEDStrip1(0);
        //bling->RunLEDStrip1(0);
    }

    if (controller->holdElevator()) {
        elevator->raiseElevator(-0.3);
    } else {
        elevator->raiseElevator(controller->elevatorSpeed());
    }

    // Cargo out
    if (controller->ejectCargo()) {
        cargo->ejectCargo();
    } else if (controller->runIntake()) {
        cargo->runIntake(1);
        cargo->holdCargo();
    } else if (controller->runIntakeReverse()) {
        cargo->reverseIntake();
    } else {
        cargo->stopFront();
        cargo->stopBack();
        cargo->stopIntake();
    }
    
    if (controller->setLimelightVisionMode()) {
        driveBase->setLimelightVision();
    } else if (controller->setLimelightCameraMode()) {
        driveBase->setLimelightCamera();
    }

    if (elevator->atMiddle()) {
        //bling->RunLeftLEDStrip(-0.17); // weird shit
        
        //bling->RunRightLEDStrip(-0.17);
    }
    else if (driveBase->getIsInHighGear()) {
        bling->RunLeftLEDStrip(0.77); // green
        bling->RunRightLEDStrip(0.77);
    }
    else {
        bling->RunLeftLEDStrip(0.69); // yellow
        bling->RunRightLEDStrip(0.69);
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
