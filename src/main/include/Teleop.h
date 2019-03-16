#ifndef TELEOP_H
#define TELEOP_H

#include "Subsystems/DriveBase.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Bling.h"
#include "Subsystems/Cargo.h"
#include "Controls/GenericController.h"

#include <frc/WPILib.h>

class Teleop {
private:
    DriveBase *driveBase;
    Claw *claw;
    Elevator *elevator;
    Bling *bling;
    Cargo *cargo;
    GenericController *controller;
public:
    Teleop(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller);
    void init();
    void periodic();   
};

#endif