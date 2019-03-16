#include "Auto/NullAuto.h"

/**
 * Initializes the null auto routine
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
NullAuto::NullAuto(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller, teleop)
{
    autoState = AutoState::init;
}

/**
 * Gives the driver teleop controls during the sandstorm
 * 
 * @author Dominic Rutkowski
 * @since 3-16-2019
 */ 
void NullAuto::run() {
    switch (autoState) {
        case AutoState::init:
            teleop->init();
            autoState = AutoState::done;
            break;
        case AutoState::done:
            teleop->periodic();
            break;
    }
}