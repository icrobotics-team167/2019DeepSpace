#include "Subsystems/Claw.h"

Claw::Claw() {
    // Claw opening and closing solenoids
    clawSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_SOLENOID);
    
    // Claw raising and lowering solenoid
    pivotSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, PIVOT_SOLENOID);
}

Claw::~Claw() {
    // Claw opening and closing solenoids
    delete clawSolenoid;

    // Claw raising and lowering solenoid
    delete pivotSolenoid;
}

/**
 * Opens the claw
 * 
 * @author Vladimir Tivanski
 * @since 2-9-2019
 */
void Claw::openClaw() {
    clawSolenoid->Set(true);
}

/**
 * Closes the claw
 * 
 * @author Vladimir Tivanski
 * @since 2-9-2019
 */
void Claw::closeClaw() {
    clawSolenoid->Set(false);
}

void Claw::moveClawUp() {
    pivotSolenoid->Set(true);
}

void Claw::moveClawDown() {
    pivotSolenoid->Set(false);
}