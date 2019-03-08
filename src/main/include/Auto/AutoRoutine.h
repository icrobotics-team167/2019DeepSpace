#ifndef AUTO_ROUTINE_H
#define AUTO_ROUTINE_H

#include "Subsystems/DriveBase.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Bling.h"
#include "Subsystems/Cargo.h"
#include "Controls/GenericController.h"

#include <frc/WPILib.h>

/**
 * Interface for auto routines
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
class AutoRoutine {
protected:
    DriveBase *driveBase;
    Claw *claw;
    Elevator *elevator;
    Bling *bling;
    Cargo *cargo;
    GenericController *controller;
public:
    AutoRoutine(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller);
    virtual void run() = 0;
};

#endif