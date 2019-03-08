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
RightBackRocket::RightBackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
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
            claw->moveClawDown();
            autoState = AutoState::openClaw;
            Wait(0.7);
            break;
        case AutoState::openClaw:
            claw->openClaw();
            autoState = AutoState::driveOffHAB;
            Wait(0.1);
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
            if (driveBase->pointTurn(25, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::driveBack;
                Wait(0.1);
            }
            break;
        case AutoState::driveBack:
            if (driveBase->straightDrive(124, -1)) {
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
            if (driveBase->straightDrive(30, -1)) {
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
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::driveToHumanPlayer:
            if (driveBase->straightDrive(150, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::driveCloserToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToHumanPlayer:
            if (driveBase->driveToReflection(0.35)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoHumanPlayer;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoHumanPlayer:
            if (driveBase->straightDrive(24, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::pickUpHatch;
                Wait(0.3);
            }
            break;
        case AutoState::pickUpHatch:
            claw->openClaw();
            if (driveBase->straightDrive(20, -0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnToRocketAgain;
                Wait(0.1);
            }
            break;
        case AutoState::turnToRocketAgain:
            if (driveBase->pointTurn(158, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::startToRocketAgain;
                Wait(0.1);
            }
            break;
        case AutoState::startToRocketAgain:
            if (driveBase->driveToReflection(0.45)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::done;
                Wait(0.2);
            }
            break;
        case AutoState::done:
            driveBase->setHighGear();
            break;
    }
}