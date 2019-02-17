#include "Auto/NullAuto.h"

/**
 * Initializes the null auto routine
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
NullAuto::NullAuto(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
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
void NullAuto::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            autoState = AutoState::done;
            break;
        case AutoState::done:
            break;
    }
}