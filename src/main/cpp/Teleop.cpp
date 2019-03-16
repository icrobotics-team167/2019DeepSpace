#include "Teleop.h"

Teleop::Teleop(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller) {
    this->driveBase = driveBase;
    this->claw = claw;
    this->elevator = elevator;
    this->bling = bling;
    this->cargo = cargo;
    this->controller = controller;
}

void Teleop::init() {
    driveBase->setLimelightCamera();
    driveBase->setHighGear();
    bling->runBothLEDStrips(bling->SOLID_GREEN);
}

void Teleop::periodic() {
    // Driving
    double leftY = controller->drivetrainLeftSpeed();
    double rightY = controller->drivetrainRightSpeed();
    
    if (controller->limelightDrive()) {
        driveBase->teleopDriveToReflection(0.2);
    } else if (controller->straightDrive()) {
        driveBase->teleopStraightDrive(leftY);
        driveBase->resetEncoders();
    } else {
        driveBase->resetPID();
        driveBase->updateNavx();
        driveBase->drive(leftY, rightY);
    }
    
    // Open and close claw
    if (controller->closeClaw()) {
        claw->closeClaw();
    } else if (controller->openClaw()) {
        claw->openClaw();
    }

    // Gear shifting
    if (controller->setLowGear()) {
        driveBase->setLowGear();
    } else if (controller->setHighGear()) {
        driveBase->setHighGear();
    }

    // Claw raising and lowering
    if (controller->raiseClaw()) {
        claw->moveClawUp();
    } else if (controller->lowerClaw()) {
        claw->moveClawDown();
    }

    // Elevator
    if (controller->holdElevator()) {
        elevator->raiseElevator(-0.3);
    } else {
        elevator->raiseElevator(controller->elevatorSpeed());
    }

    // Cargo intake and ejection
    if (controller->ejectCargo()) {
        cargo->ejectCargo();
    } else if (controller->runIntake()) {
        cargo->runIntake(1);
        cargo->holdCargo();
    } else if (controller->runIntakeReverse()) {
        cargo->reverseIntake();
    } else {
        cargo->stopFront();
        cargo->stopBack();
        cargo->stopIntake();
    }
    
    // Limelight mode
    if (controller->setLimelightVisionMode()) {
        driveBase->setLimelightVision();
    } else if (controller->setLimelightCameraMode()) {
        driveBase->setLimelightCamera();
    }

    // LEDs
    if (elevator->atMiddle()) {
        // Runs LEDs if the elevator is at the middle leveL?
    } else if (driveBase->getIsInHighGear()) {
        bling->runBothLEDStrips(bling->SOLID_GREEN);
    } else {
        bling->runBothLEDStrips(bling->SOLID_YELLOW);
    }
}