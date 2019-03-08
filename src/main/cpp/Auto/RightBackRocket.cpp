#include "Auto/RightBackRocket.h"

/**
 * Initializes the right back rocket auto routine
 * 
 * @author Dominic Rutkowski
 * @since 2-15-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
RightBackRocket::RightBackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller)
{
    autoState = AutoState::init;
}

/**
 * Scores on the right back rocket and almost scores
 * on the right front rocket
 *  
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */ 
void RightBackRocket::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            driveBase->setLowGear();
            driveBase->setLimelightVision();
            claw->openClaw();
            autoState = AutoState::driveOffHAB;
            break;
        case AutoState::driveOffHAB:
            if (driveBase->straightDrive(45, -0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::alignWithBack;
                Wait(0.1);
            }
            break;
        case AutoState::alignWithBack:
            if (driveBase->pointTurn(23, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                Wait(0.35);
                claw->closeClaw();
                Wait(0.25);
                claw->moveClawDown();
                autoState = AutoState::openClaw;
                Wait(0.36);
            }
            break;
        case AutoState::openClaw:
            claw->openClaw();
            autoState = AutoState::driveBack;
            Wait(0.1);
            break;
        case AutoState::driveBack:
            if (driveBase->straightDrive(135, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::turnToRocket:
            if (driveBase->pointTurn(-45, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::driveToRocket:
            if (driveBase->driveToReflection(0.35)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoRocket;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoRocket:
            if (driveBase->straightDrive(30, 0.55)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::score;
                Wait(0.6);
            }
            break;
        case AutoState::score:
            claw->closeClaw();
            if (driveBase->straightDrive(32, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsHumanPlayer:
            if (driveBase->pointTurn(15, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();

                // driveBase->setLimelightCamera();
                // driveBase->setHighGear();
                // bling->RunLeftLEDStrip(0.77); // green
                // bling->RunRightLEDStrip(0.77);
                // // claw->moveClawDown();
                // driveBase->setHighGear();
                // bling->RunLeftLEDStrip(0.77); // green
                // bling->RunRightLEDStrip(0.77);
                // // Wait(0.5);
                // claw->openClaw();

                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        // case AutoState::teleop:
        //     // Driving
        //     double leftY = controller->getDrivetrainLeftSpeed();
        //     double rightY = controller->getDrivetrainRightSpeed();
            
        //     if (controller->getDriveWithLimelight()) {
        //         driveBase->teleopDriveToReflection(0.2);
        //     } else if (controller->getDriveStraight()) {
        //         driveBase->teleopStraightDrive(leftY);
        //         driveBase->resetEncoders();
        //     } else {
        //         driveBase->resetPID();
        //         driveBase->updateNavx();
        //         driveBase->drive(leftY, rightY);
        //     }
            
        //     // Open and close claw
        //     if (controller->getCloseClaw()) {
        //         claw->closeClaw();
        //         //bling->RunLEDStrip1(0);
        //         //bling->RunLEDStrip1(0);
        //     } else if (controller->getOpenClaw()) {
        //         claw->openClaw();
        //         //bling->RunLEDStrip1(0);
        //         //bling->RunLEDStrip1(0);
        //     }

        //     // Gear shifting
        //     if (controller->getSetLowGear()) {
        //         driveBase->setLowGear();
        //         bling->RunLeftLEDStrip(0.69); // yellow
        //         bling->RunRightLEDStrip(0.69); 
        //     } else if (controller->getSetHighGear()) {
        //         driveBase->setHighGear();
        //         bling->RunLeftLEDStrip(0.77); // green
        //         bling->RunRightLEDStrip(0.77);
        //     }

        //     // Claw raising and lowering
        //     if (controller->getRaiseClaw()) {
        //         claw->moveClawUp();
        //         //bling->RunLEDStrip1(0);
        //         //bling->RunLEDStrip1(0);
        //     } else if (controller->getLowerClaw()) {
        //         claw->moveClawDown();
        //         //bling->RunLEDStrip1(0);
        //         //bling->RunLEDStrip1(0);
        //     }

        //     elevator->raiseElevator(controller->getElevatorSpeed());

        //     // Cargo out
        //     if (controller->getRunFrontOut()) {
        //         cargo->ejectCargo();
        //     } else if (controller->getRunIntake()) {
        //         cargo->runIntake(1);
        //         cargo->holdCargo();
        //     } else if (controller->getReverseIntake()) {
        //         cargo->reverseIntake();
        //     } else {
        //         cargo->stopFront();
        //         cargo->stopBack();
        //         cargo->stopIntake();
        //     }
            
        //     if (controller->getSetLimelightVision()) {
        //         driveBase->setLimelightVision();
        //     } else if (controller->getSetLimelightCamera()) {
        //         driveBase->setLimelightCamera();
        //     }

        //     if (elevator->atMiddle()) {
        //         //bling->RunLeftLEDStrip(0.67); // gold
        //         //bling->RunRightLEDStrip(0.67);
        //     }
        //     else if (driveBase->getIsInHighGear()) {
        //         bling->RunLeftLEDStrip(0.77); // green
        //         bling->RunRightLEDStrip(0.77);
        //     }
        //     else {
        //         bling->RunLeftLEDStrip(0.69); // yellow
        //         bling->RunRightLEDStrip(0.69);
        //     }
        //     break;
        // case AutoState::driveToHumanPlayer:
        //     if (driveBase->straightDrive(150, 1)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         driveBase->setLowGear();
        //         autoState = AutoState::driveCloserToHumanPlayer;
        //         Wait(0.1);
        //     }
        //     break;
        // case AutoState::driveCloserToHumanPlayer:
        //     if (driveBase->driveToReflection(0.35)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::driveIntoHumanPlayer;
        //         Wait(0.2);
        //     }
        //     break;
        // case AutoState::driveIntoHumanPlayer:
        //     if (driveBase->straightDrive(24, 0.5)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::pickUpHatch;
        //         Wait(0.3);
        //     }
        //     break;
        // case AutoState::pickUpHatch:
        //     claw->openClaw();
        //     if (driveBase->straightDrive(20, -0.5)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::turnToRocketAgain;
        //         Wait(0.1);
        //     }
        //     break;
        // case AutoState::turnToRocketAgain:
        //     if (driveBase->pointTurn(158, 1)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::startToRocketAgain;
        //         Wait(0.1);
        //     }
        //     break;
        // case AutoState::startToRocketAgain:
        //     if (driveBase->driveToReflection(0.45)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::done;
        //         Wait(0.2);
        //     }
        //     break;
        case AutoState::done:
            driveBase->setHighGear();
            break;
    }
}