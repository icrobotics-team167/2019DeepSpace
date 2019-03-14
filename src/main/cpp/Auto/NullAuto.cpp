#include "Auto/NullAuto.h"

/**
 * Initializes the null auto routine
 * 
 * @author Dominic Rutkowski
 * @since 2-15-2019
 * 
 * @param *driveBase A pointer to the DriveBase subsystem
 * @param *claw A pointer to the Claw subsystem
 * @param *elevator A pointer to the Elevator subsystem
 * @param *bling A pointer to the Bling subsystem
 * @param *Cargo A pointer to the Cargo subsystem
 */ 
NullAuto::NullAuto(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller):
AutoRoutine(driveBase, claw, elevator, bling, cargo, controller)
{
    
    autoState = AutoState::init;
}

/**
 * Sits on the HAB platform for 15 seconds
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 */ 
void NullAuto::run() {
    switch (autoState) {
        case AutoState::init:
            driveBase->resetEncoders();
            driveBase->updateNavx();
            double leftY = controller->getDrivetrainLeftSpeed();
            double rightY = controller->getDrivetrainRightSpeed();
            
            if (controller->getDriveWithLimelight()) {
                driveBase->teleopDriveToReflection(0.2);
            } else if (controller->getDriveStraight()) {
                driveBase->teleopStraightDrive(leftY);
                driveBase->resetEncoders();
            } else {
                driveBase->resetPID();
                driveBase->updateNavx();
                driveBase->drive(leftY, rightY);
            }
            
            // Open and close claw
            if (controller->getCloseClaw()) {
                claw->closeClaw();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            } else if (controller->getOpenClaw()) {
                claw->openClaw();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            }

            // Gear shifting
            if (controller->getSetLowGear()) {
                driveBase->setLowGear();
                bling->RunLeftLEDStrip(0.69); // yellow
                bling->RunRightLEDStrip(0.69); 
            } else if (controller->getSetHighGear()) {
                driveBase->setHighGear();
                bling->RunLeftLEDStrip(0.77); // green
                bling->RunRightLEDStrip(0.77);
            }

            // Claw raising and lowering
            if (controller->getRaiseClaw()) {
                claw->moveClawUp();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            } else if (controller->getLowerClaw()) {
                claw->moveClawDown();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            }

            if (controller->getHoldElevator()) {
                elevator->raiseElevator(-0.3);
            } else {
                elevator->raiseElevator(controller->getElevatorSpeed());
            }

            // Cargo out
            if (controller->getRunFrontOut()) {
                cargo->ejectCargo();
            } else if (controller->getRunIntake()) {
                cargo->runIntake(1);
                cargo->holdCargo();
            } else if (controller->getReverseIntake()) {
                cargo->reverseIntake();
            } else {
                cargo->stopFront();
                cargo->stopBack();
                cargo->stopIntake();
            }
            
            if (controller->getSetLimelightVision()) {
                driveBase->setLimelightVision();
            } else if (controller->getSetLimelightCamera()) {
                driveBase->setLimelightCamera();
            }

            if (elevator->atMiddle()) {
                bling->RunLeftLEDStrip(0.61); // red
                bling->RunRightLEDStrip(0.61);
            }
            else if (driveBase->getIsInHighGear()) {
                bling->RunLeftLEDStrip(0.77); // green
                bling->RunRightLEDStrip(0.77);
            }
            else {
                bling->RunLeftLEDStrip(0.69); // yellow
                bling->RunRightLEDStrip(0.69);
            }
            break;
        // case AutoState::done:
        //     break;
    }
}