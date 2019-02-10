#include "Auto/EncoderTest.h"

#include <frc/WPILib.h>

EncoderTest::EncoderTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo) {
    this->driveBase = driveBase;
    this->claw = claw;
    this->elevator = elevator;
    this->bling = bling;
    this->cargo = cargo;
    autoState = AutoState::init;
}

void EncoderTest::run() {
}