#include "Auto/CargoShip.h"

/**
 * Initializes the cargo ship auto routine
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
CargoShip::CargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    autoState = AutoState::init;
}

/**
 * Sits on the HAB platform for 15 seconds
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void CargoShip::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            driveBase->setLowGear();
            driveBase->setLimelightVision();
            claw->moveClawDown();
            autoState = AutoState::openClaw;
            Wait(0.5);
            break;
        case AutoState::openClaw:
            claw->openClaw();
            autoState = AutoState::driveToCargoShipFront;
            Wait(0.1);
            break;
        case AutoState::driveToCargoShipFront:
            if (driveBase->driveToReflection(0.6)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoCargoShipFront;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoCargoShipFront:
            if (driveBase->straightDrive(24, 0.55)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::score;
                Wait(0.6);
            }
            break;
        case AutoState::score:
            claw->closeClaw();
            if (driveBase->straightDrive(20, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsHumanPlayer:
            if (driveBase->pointTurn(-135, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateLimelight();
                driveBase->setHighGear();
                autoState = AutoState::driveCloserToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToHumanPlayer:
            if (driveBase->straightDrive(130, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnTowardsHumanPlayerAgain;
                Wait(0.3);
            }
            break;
        case AutoState::turnTowardsHumanPlayerAgain:
            if (driveBase->pointTurn(135, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateLimelight();
                autoState = AutoState::driveToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveToHumanPlayer:
            if (driveBase->driveToReflection(0.6)) {
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
            if (driveBase->straightDrive(20, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveFromHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveFromHumanPlayer:
            if (driveBase->straightDrive(130, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShip:
            if (driveBase->pointTurn(30, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveCloserToCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToCargoShip:
            if (driveBase->straightDrive(123, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsCargoShipAgain;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShipAgain:
            if (driveBase->pointTurn(-120, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveToCargoShipSide;
                Wait(0.1);
            }
            break;
        case AutoState::driveToCargoShipSide:
            if (driveBase->driveToReflection(0.35)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoCargoShipSide;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoCargoShipSide:
            if (driveBase->straightDrive(24, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::scoreAgain;
                Wait(0.6);
            }
            break;
        case AutoState::scoreAgain:
            claw->closeClaw();
            if (driveBase->straightDrive(20, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::done:
            break;
    }
}