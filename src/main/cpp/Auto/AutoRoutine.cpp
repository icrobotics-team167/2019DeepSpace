#include "Auto/AutoRoutine.h"

#include <frc/WPILib.h>

/**
 * Initializes pointers to the subsystems of an auto routine
 * and updates the navx init value in preparation for auto
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
AutoRoutine::AutoRoutine(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop) {
    this->driveBase = driveBase;
    this->claw = claw;
    this->elevator = elevator;
    this->bling = bling;
    this->cargo = cargo;
    this->controller = controller;
    this->teleop = teleop;

    driveBase->updateNavx();
}