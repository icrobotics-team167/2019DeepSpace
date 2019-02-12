#include "Auto/AutoRoutine.h"

#include <frc/WPILib.h>

/**
 * Initializes pointers to the subsystems of an auto routine
 * and updates the navx init value in preparation for auto
 * 
 * @author Dominic Rutkowski
 * @since 2-11-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
AutoRoutine::AutoRoutine(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo) {
    this->driveBase = driveBase;
    this->claw = claw;
    this->elevator = elevator;
    this->bling = bling;
    this->cargo = cargo;

    driveBase->updateNavx();
}