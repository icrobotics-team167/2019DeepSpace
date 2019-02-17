#include "Auto/LimelightTest.h"

/**
 * Initializes the Limelight test auto routine
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
LimelightTest::LimelightTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    autoState = AutoState::init;
}

/**
 * Drives to the Limelight vision target
 * 
 * @author Dominic Rutkowski
 * @since 2-17-2019
 */ 
void LimelightTest::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            driveBase->setHighGear();
            autoState = AutoState::limelightTest;
            break;
        case AutoState::limelightTest:
            if (driveBase->driveToReflection(0.15)) {
                driveBase->resetEncoders();
                driveBase->updateNavx();
                autoState = AutoState::done;
            }
            break;
        case AutoState::done:
            break;
    }
}