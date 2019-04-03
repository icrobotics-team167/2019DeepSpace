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
            driveBase->setLimelightLeft();
            Wait(0.36);
            break;
        case AutoState::openClaw:
            claw->openClaw();
            autoState = AutoState::driveOffHAB;
            Wait(0.1);
            break;
        case AutoState::driveOffHAB: 
            if (driveBase->straightDrive(75, 1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setLowGear();
                driveToCargoShipFrontInitialHeading = driveBase->getNavx()->GetAngle();
                autoState = AutoState::driveToCargoShipFront;
                Wait(0.2);
            }                                   
            break;
        case AutoState::driveToCargoShipFront:
            if (driveBase->driveHeading(35.5, 0.75, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveIntoCargoShipFrontInitialHeading = driveBase->getNavx()->GetAngle();
                autoState = AutoState::driveIntoCargoShipFront;
            }
            break;
        case AutoState::driveIntoCargoShipFront:           
            if (driveBase->driveHeading(20, 0.5, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::score;
                driveBase->drive(0,0);
                Wait(0.3);
            }
            break;
        case AutoState::score:
            claw->closeClaw();
            Wait(0.15);
            if (driveBase->straightDrive(15, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveByHumanPlayerHeading = driveBase->getNavx()->GetAngle() - 85;
                autoState = AutoState::driveByHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveByHumanPlayer:
            if (driveBase->driveHeading(67, 1, driveByHumanPlayerHeading)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsHumanPlayerAgain;
                Wait(0.1);
            }
            break;
        // case AutoState::turnTowardsHumanPlayer:
        //     if (driveBase->pointTurn(-110, 0.7)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         driveBase->updateLimelight();
        //         driveBase->setHighGear();
        //         autoState = AutoState::driveCloserToHumanPlayer;
        //         Wait(0.1);
        //     }
        //     break;
        // case AutoState::driveCloserToHumanPlayer:
        //     if (driveBase->straightDrive(96.5, 1)) {
        //         driveBase->resetEncoders();
        //         driveBase->updateNavx();
        //         driveBase->setLowGear();
        //         driveBase->setLimelightLowest();
        //         autoState = AutoState::turnTowardsHumanPlayerAgain;
        //         Wait(0.2);
        //     }
        //     break;
        case AutoState::turnTowardsHumanPlayerAgain:
            if (driveBase->pointTurn(-38, 0.85)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->updateLimelight();
                driveBase->setHighGear();
                autoState = AutoState::driveToHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveToHumanPlayer:
            if (driveBase->driveHeading(27.5, 0.75, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoHumanPlayer;
            }
            break;
        case AutoState::driveIntoHumanPlayer:
            if (driveBase->driveHeading(33.5, 0.5, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::pickUpHatch;
                Wait(0.5);
            }
            break;
        case AutoState::pickUpHatch:
            claw->openClaw();
            if (driveBase->straightDrive(30, -1)) { // 140
                driveBase->resetEncoders();
                driveBase->updateNavx();
                cargoShipSideHeading = driveBase->getNavx()->GetAngle() + 27.5;
                autoState = AutoState::driveCloserToCargoShip;
                Wait(0.5);
            }
            break;
        case AutoState::driveCloserToCargoShip:
            if (driveBase->driveHeading(149, -1, cargoShipSideHeading)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsCargoShipAgain;
                Wait(0.1); 
            }
            break;
        case AutoState::turnTowardsCargoShipAgain:
            if (driveBase->pointTurn(-56, 0.5)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLimelightRight();
                autoState = AutoState::driveIntoCargoShipSide;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoCargoShipSide:
            driveBase->driveHeading(10000000, 0.35, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx());
            if (driveBase->getLimelightTa() >= 17.2) {
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