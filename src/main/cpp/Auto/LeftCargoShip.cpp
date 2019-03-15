#include "Auto/LeftCargoShip.h"

/**
 * Initializes the left cargo ship auto routine
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
LeftCargoShip::LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController* controller):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller)
{
    autoState = AutoState::init;
}

/**
 * Scores on the front left cargo ship and almost scores
 * on the side left cargo ship
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void LeftCargoShip::run() {
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
            autoState = AutoState::driveOffHAB;
            Wait(0.1);
            break;
        case AutoState::driveOffHAB:
            if (driveBase->straightDrive(24, 0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveToCargoShipFront;
                Wait(0.1);
            }
            break;
        case AutoState::driveToCargoShipFront:
            if (driveBase->driveToReflection(0.35)) {
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
            if (driveBase->straightDrive(14, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsHumanPlayer:
            if (driveBase->pointTurn(-110, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setHighGear();
                autoState = AutoState::driveCloserToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToHumanPlayer:
            if (driveBase->straightDrive(102.5, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnTowardsHumanPlayerAgain;
                Wait(0.3);
            }
            break;
        case AutoState::turnTowardsHumanPlayerAgain:
            if (driveBase->pointTurn(-58, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                autoState = AutoState::driveToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveToHumanPlayer:
            if (driveBase->driveToReflection(0.35)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoHumanPlayer;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoHumanPlayer:
            if (driveBase->straightDrive(26, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::pickUpHatch;
                Wait(0.6);
            }
            break;
        case AutoState::pickUpHatch:
            claw->openClaw();
            if (driveBase->straightDrive(40, -1)) { // 140
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShip:
            if (driveBase->pointTurn(25, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::driveCloserToCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToCargoShip:
            if (driveBase->straightDrive(72.5, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnTowardsCargoShipAgain;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShipAgain:
            if (driveBase->pointTurn(-120, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::done;
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