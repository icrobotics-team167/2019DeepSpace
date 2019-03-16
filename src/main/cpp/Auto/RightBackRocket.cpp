#include "Auto/RightBackRocket.h"

/**
 * Initializes the right back rocket auto routine
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
RightBackRocket::RightBackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller, teleop)
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
                autoState = AutoState::done;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoRocket:
            if (driveBase->straightDrive(40, 0.55)) {
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
                autoState = AutoState::done;
                Wait(0.1);
            }
            break;
        case AutoState::done:
            driveBase->setHighGear();
            break;
    }
}