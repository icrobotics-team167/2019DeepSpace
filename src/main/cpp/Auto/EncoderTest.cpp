#include "Auto/EncoderTest.h"

EncoderTest::EncoderTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo) {
    this->driveBase = driveBase;
    this->claw = claw;
    this->elevator = elevator;
    this->bling = bling;
    this->cargo = cargo;

    leftEncoder = driveBase->getLeftEncoder();
    rightEncoder = driveBase->getRightEncoder();
    autoState = AutoState::init;
}

void EncoderTest::run() {
    switch (autoState) {
        case AutoState::init:
            leftEncoder->Reset();
            rightEncoder->Reset();
            autoState = AutoState::test;
            break;
        case AutoState::test:
            SmartDashboard::PutNumber("Left encoder: ", leftEncoder->Get());
            SmartDashboard::PutNumber("Right encoder: ", rightEncoder->Get());
            driveBase->tankDrive(0.3, 0.3);
            break;
    }
}