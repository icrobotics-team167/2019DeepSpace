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
 * Scores on the front left cargo ship, picks up a hatch from the left
 * human player station, and scores on the side left cargo ship
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void LeftCargoShip::run() {
    if (controller->sandstormAutoOverride()) {
        teleop->init();
        autoState = AutoState::done;
    }
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
                driveBase->setHighGear();                
                driveByHumanPlayerHeading = driveBase->getNavx()->GetAngle() - 85;
                autoState = AutoState::driveByHumanPlayer;
                Wait(0.1);
            }
            break;
        case AutoState::driveByHumanPlayer:
            if (driveBase->driveHeading(64, 1, driveByHumanPlayerHeading)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnTowardsHumanPlayerAgain;
                Wait(0.1);
            }
            break;
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
                driveBase->setLimelightLowestHatchPickup();
                autoState = AutoState::driveIntoHumanPlayer;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoHumanPlayer:
            if (driveBase->driveHeading(20.5, 0.35, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::pickUpHatch;
                Wait(0.5);
            }
            break;
        case AutoState::pickUpHatch:
            claw->openClaw();
            if (driveBase->driveHeading(30, -1, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx())) { // 140
                driveBase->resetEncoders();
                driveBase->updateNavx();
                cargoShipSideHeading = driveBase->getNavx()->GetAngle() + 22.5;
                autoState = AutoState::driveCloserToCargoShip;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToCargoShip:
            if (driveBase->driveHeading(85, -1, cargoShipSideHeading)) { //149 inches
                driveBase->resetEncoders();
                driveBase->updateNavx();
                cargoShipSideHeading = driveBase->getNavx()->GetAngle() - 22.5;
                autoState = AutoState::driveCloserToCargoShipAgain;
                Wait(0.1); 
            }
            break;
        case AutoState::driveCloserToCargoShipAgain:
            if (driveBase->driveHeading(75, -1, cargoShipSideHeading)) { 
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->drive(0,0);
                autoState = AutoState::turnTowardsCargoShipAgain;
                Wait(0.2); 
            }
            break;
        case AutoState::turnTowardsCargoShipAgain:
            if (driveBase->pointTurn(-68, 0.4)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLimelightRight();
                driveBase->drive(0,0);
                autoState = AutoState::driveIntoCargoShipSide;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoCargoShipSide:
            driveBase->driveHeading(25, 0.5, driveBase->getNavx()->GetAngle() + driveBase->getLimelightTx());
            if (driveBase->getLimelightTa() >= 17.2) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->drive(0,0);
                autoState = AutoState::scoreAgain;
                Wait(0.3);
            }
            break;
        case AutoState::scoreAgain:
            claw->closeClaw();
            autoState = AutoState::done; //comment these 2 lines out if you uncomment
            Wait(0.1);                   //below IF statement
            
            // if (driveBase->straightDrive(20, -1)) {
            //     driveBase->resetEncoders();
            //     driveBase->updateNavx();
            //     teleop->init();
            //     autoState = AutoState::done;
            //     Wait(0.1);
            // }
            break;
        case AutoState::done:
            teleop->periodic();
            break;
    }
}