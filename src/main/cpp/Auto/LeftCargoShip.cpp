#include "Auto/LeftCargoShip.h"

/**
 * Initializes the left cargo ship auto routine
 * 
 * @author Dominic Rutkowski
 * @since 3-15-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *cargo A pointer to the Cargo subsystem
 * @param *controller A pointer to the controller abstraction
 * @param *teleop A pointer to the teleop routine
 */ 
LeftCargoShip::LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController* controller, Teleop *teleop):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller, teleop)
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
            break;                  // there is an error sometimes in which after the robot drives off of the hab platform it just stops and does not move
                                    // we found that this error is resolved if the robot is simply pushed forward, then it will continue autonomous -- but we cannot push the robot at a competition
        case AutoState::driveOffHAB: // possible cause of error:
            if (driveBase->straightDrive(95, 1)) { // this might not be goinging far enough
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setLowGear();
                autoState = AutoState::alignWithCargoShip;
                Wait(0.2);
                SmartDashboard::PutBoolean("Finished Driving of Hab: ", true); // check if this case ever ends
            }                                   
            break;
        case AutoState::alignWithCargoShip: // possible cause of error:
            // if (driveBase->alignWithTarget()) {
            if (driveBase->pointTurn(driveBase->getLimelightTx(), 0.2)) { // this might be too slow for a not full battery
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                autoState = AutoState::checkIsAlignedWithCargoShipFront;
                Wait(0.1);
                SmartDashboard::PutBoolean("Finished Aligning with Cargo Ship: ", true); // check if this case ever ends
            }
            break;
        case AutoState::checkIsAlignedWithCargoShipFront:
            Wait(0.05);
            if (abs(driveBase->getLimelightTx()) <= 0.6) {
                autoState = AutoState::driveIntoCargoShipFront;
            } else {
                autoState = AutoState::alignWithCargoShip;
            }
            break;
        // case AutoState::driveToCargoShipFront:
        //     if (driveBase->driveToReflection(0.2)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::driveIntoCargoShipFront;
        //         Wait(0.2);
        //     }
        //     break;
        case AutoState::driveIntoCargoShipFront: // possible cause of error
            if (driveBase->straightDrive(24, .55)) { // this could just not be driving but this is unlikely
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::score;
                Wait(0.3);
            }
            break;
        case AutoState::score:
            claw->closeClaw();
            if (driveBase->straightDrive(8, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsHumanPlayer:
            if (driveBase->pointTurn(-115, 0.7)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setHighGear();
                autoState = AutoState::driveCloserToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToHumanPlayer:
            if (driveBase->straightDrive(108.5, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnTowardsHumanPlayerAgain;
                Wait(0.2);
            }
            break;
        case AutoState::turnTowardsHumanPlayerAgain:
            if (driveBase->pointTurn(-40, 0.85)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                autoState = AutoState::alignWithHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::alignWithHumanPlayer:
            // if (driveBase->alignWithTarget()) {
            if (driveBase->pointTurn(driveBase->getLimelightTx(), 0.2)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setLowGear();
                autoState = AutoState::checkIsAlignedWithHumanPlayer;
                Wait(0.2);
            }
            break;
        case AutoState::checkIsAlignedWithHumanPlayer:
            Wait(0.05);
            if (abs(driveBase->getLimelightTx()) <= 0.6) {
                autoState = AutoState::driveToHumanPlayer;
            } else {
                autoState = AutoState::alignWithHumanPlayer;
            }
            break;
        case AutoState::driveToHumanPlayer:
            if (driveBase->straightDrive(55, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::driveIntoHumanPlayer;
                Wait(0.2);
            }
            break;
        // case AutoState::limelightToPlayer:
        //     if (driveBase->driveToReflection(0.2)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::alignWithHumanPlayerAgain;
        //         Wait(0.2);
        //     }
        //     break;
        // case AutoState::alignWithHumanPlayerAgain:
        //     if (driveBase->alignWithTarget()) {
        //     // if (driveBase->pointTurn(driveBase->getLimelightTx(), 0.2)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         driveBase->updateLimelight();
        //         driveBase->setLowGear();
        //         autoState = AutoState::driveIntoHumanPlayer;
        //         Wait(0.2);
        //     }
        //     break;
        case AutoState::driveIntoHumanPlayer:
            if (driveBase->straightDrive(15, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::pickUpHatch;
                Wait(0.3);
            }
            break;
        case AutoState::pickUpHatch:
            claw->openClaw();
            if (driveBase->straightDrive(40, -1)) { // 140
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShip:
            if (driveBase->pointTurn(5, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveCloserToCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToCargoShip:
            if (driveBase->straightDrive(127, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsCargoShipAgain;
                Wait(0.1);
            }
            break;
        case AutoState::turnTowardsCargoShipAgain:
            if (driveBase->pointTurn(-75, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLimelightRight();
                autoState = AutoState::alignWithCargoShipSideAgain;
                Wait(1);
            }
            break;
        case AutoState::alignWithCargoShipSideAgain:
            if (driveBase->pointTurn(driveBase->getLimelightTx(), 0.2)) { // this might be too slow for a not full battery
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        // case AutoState::driveToCargoShipSide:
        //     if (driveBase->driveToReflection(0.35)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         autoState = AutoState::driveIntoCargoShipSide;
        //         Wait(0.1);
        //     }
        //     break;
        case AutoState::driveIntoCargoShipSide:
            if (driveBase->straightDrive(48, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::scoreAgain;
                Wait(0.3);
            }
            break;
        case AutoState::scoreAgain:
            claw->closeClaw();
            if (driveBase->straightDrive(20, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                teleop->init();
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::done:
            teleop->periodic();
            break;
    }
}