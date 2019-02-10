#include "Auto/EncoderTest.h"

/**
 * Initializes the encoder test auto routine
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
EncoderTest::EncoderTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo):
AutoRoutine(driveBase, claw, elevator, bling, cargo)
{
    leftEncoder = driveBase->getLeftEncoder();
    rightEncoder = driveBase->getRightEncoder();
    autoState = AutoState::init;
}

/**
 * Drives forward at 0.3 power and test the encoders
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void EncoderTest::run() {
    switch (autoState) {
        case AutoState::init:
            leftEncoder->Reset();
            rightEncoder->Reset();
            driveBase->navxInitValue = driveBase->getNavx()->GetAngle();
            autoState = AutoState::test;
            break;
        case AutoState::test:
            SmartDashboard::PutNumber("Left encoder: ", leftEncoder->Get());
            SmartDashboard::PutNumber("Right encoder: ", rightEncoder->Get());
            driveBase->straightDrive(100, 0.3);
            break;
    }
}