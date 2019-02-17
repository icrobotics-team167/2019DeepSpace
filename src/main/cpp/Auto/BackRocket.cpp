#include "Auto/BackRocket.h"

/**
 * Initializes the back rocket auto routine
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
BackRocket::BackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    autoState = AutoState::init;
}

/**
 * Scores on the back rocket
 *  
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */ 
void BackRocket::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            driveBase->setLowGear();
            driveBase->setLimelightVision();
            claw->moveClawDown();
            autoState = AutoState::driveOffHAB;
            Wait(0.1);
            break;
        case AutoState::driveOffHAB:
            if (driveBase->straightDrive(47, -0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::alignWithBack;
                Wait(0.1);
            }
            break;
        case AutoState::alignWithBack:
            if (driveBase->pointTurn(-20, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setHighGear();
                autoState = AutoState::driveBack;
                Wait(0.1);
            }
            break;
        case AutoState::driveBack:
            if (driveBase->straightDrive(166, -1)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                driveBase->setLowGear();
                autoState = AutoState::turnToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::turnToRocket:
            if (driveBase->pointTurn(40, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::driveToRocket:
            if (driveBase->driveToReflection(0.25)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveIntoRocket;
                Wait(0.2);
            }
            break;
        case AutoState::driveIntoRocket:
            if (driveBase->straightDrive(27, 0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::score;
                Wait(0.3);
            }
            break;
        case AutoState::score:
            claw->closeClaw();
            if (driveBase->straightDrive(10, -0.6)) {
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