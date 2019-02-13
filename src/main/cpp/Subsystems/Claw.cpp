#include "Subsystems/Claw.h"

Claw::Claw() {
    // Claw opening and closing solenoid
    clawOpenSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_OPEN_SOLENOID);
    clawClosedSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, CLAW_CLOSED_SOLENOID);
    
    // Claw raising and lowering solenoid
    pivotSolenoid = new frc::Solenoid(PNEUMATIC_CONTROLLER, PIVOT_SOLENOID);
}

Claw::~Claw() {
    // Claw opening and closing solenoid
    delete clawOpenSolenoid;
    delete clawClosedSolenoid;

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
    clawOpenSolenoid->Set(true);
    clawClosedSolenoid->Set(false);
}

/**
 * Closes the claw
 * 
 * @author Vladimir Tivanski
 * @since 2-9-2019
 */
void Claw::closeClaw() {
    clawOpenSolenoid->Set(false);
    clawClosedSolenoid->Set(true);
}

/**
 * Raises the claw
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void Claw::moveClawUp() {
    pivotSolenoid->Set(true);
}

/**
 * Lowers the claw
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */
void Claw::moveClawDown() {
    pivotSolenoid->Set(false);
}