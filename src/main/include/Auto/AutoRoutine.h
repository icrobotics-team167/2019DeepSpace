#ifndef AUTO_ROUTINE_H
#define AUTO_ROUTINE_H

#include "Subsystems/DriveBase.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Bling.h"
#include "Subsystems/Cargo.h"
#include "Controls/GenericController.h"
#include "Teleop.h"

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
    Teleop *teleop;
public:
    AutoRoutine(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    virtual void run() = 0;
};

#endif