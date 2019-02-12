#include "Auto/AutoTest.h"

/**
 * Initializes the auto test routine
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
AutoTest::AutoTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    leftEncoder = driveBase->getLeftEncoder();
    rightEncoder = driveBase->getRightEncoder();
    autoState = AutoState::init;
}

/**
 * Drives forward at 100 inches 0.3 power and then
 * turns 180 degrees clockwise, puts encoder values
 * in the SmartDashboard
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void AutoTest::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            autoState = AutoState::drive100;
            break;
        case AutoState::drive100:
            if (driveBase->straightDrive(100, 0.3)) {
                driveBase->updateNavx();
                autoState = AutoState::turn180;
            }
            break;
        case AutoState::turn180:
            if (driveBase->pointTurn(180, 0.3)) {
                driveBase->updateNavx();
                autoState = AutoState::done;
            }
            break;
        case AutoState::done:
            break;
    }
    SmartDashboard::PutNumber("Left encoder: ", leftEncoder->Get());
    SmartDashboard::PutNumber("Right encoder: ", rightEncoder->Get());
}