#ifndef AUTO_ROUTINE_H
#define AUTO_ROUTINE_H

#include "Subsystems/DriveBase.h"
#include "Subsystems/Claw.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Bling.h"
#include "Subsystems/Cargo.h"

#include <frc/WPILib.h>

class AutoRoutine {
protected:
    DriveBase *driveBase;
    Claw *claw;
    Elevator *elevator;
    Bling *bling;
    Cargo *cargo;
public:
    virtual void run() = 0;
};

#endif