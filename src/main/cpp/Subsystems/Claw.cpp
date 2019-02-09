#include "Subsystems/Claw.h"

Claw::Claw() {
    // Claw opening and closing solenoids
    openSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_OPEN_SOLENOID);
    closedSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_CLOSED_SOLENOID);
    
    // Claw raising and lowering solenoid
    //pivotSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, PIVOT_SOLENOID);
}

Claw::~Claw() {
    // Claw opening and closing solenoids
    delete openSolenoid;
    delete closedSolenoid;

    // Claw raising and lowering solenoid
    delete pivotSolenoid;
}