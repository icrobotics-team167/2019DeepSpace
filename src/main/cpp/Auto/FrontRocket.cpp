#include "Auto/FrontRocket.h"

/**
 * Initializes the front rocket auto routine
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
FrontRocket::FrontRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    autoState = AutoState::init;
}

/**
 * Scores on the front rocket
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */ 
void FrontRocket::run() {
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
            if (driveBase->straightDrive(47, 0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::turnToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::turnToRocket:
            if (driveBase->pointTurn(-60, 0.3)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::driveCloserToRocket;
                Wait(0.1);
            }
            break;
        case AutoState::driveCloserToRocket:
            if (driveBase->straightDrive(75, 0.75)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::pointAtRocket;
                Wait(0.1);
            }
            break;
        case AutoState::pointAtRocket:
            if (driveBase->pointTurn(30, 0.3)) {
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