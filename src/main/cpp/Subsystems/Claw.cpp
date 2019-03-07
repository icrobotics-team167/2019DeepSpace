#include "Subsystems/Claw.h"

Claw::Claw() {
    // Claw opening and closing solenoid
    clawSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_SOLENOID);
    
    // Claw raising and lowering solenoid
    pivotSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, PIVOT_SOLENOID);
    pivotSolenoidReversed = new frc::Solenoid(PNEUMATIC_CONTROLLER, PIVOT_SOLENOID_REVERSED);
}

Claw::~Claw() {
    // Claw opening and closing solenoid
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

/**
 * Raises the claw
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void Claw::moveClawUp() {
    pivotSolenoid->Set(false);
    pivotSolenoidReversed->Set(true);
}

/**
 * Lowers the claw
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void Claw::moveClawDown() {
    pivotSolenoid->Set(true);
    pivotSolenoidReversed->Set(false);
}