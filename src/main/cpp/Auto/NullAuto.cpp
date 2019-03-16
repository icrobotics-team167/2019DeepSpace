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
            driveBase->setLimelightCamera();
            driveBase->setHighGear();
            bling->RunLeftLEDStrip(0.77); // green
            bling->RunRightLEDStrip(0.77);
            // claw->moveClawDown();
            driveBase->setHighGear();
            bling->RunLeftLEDStrip(0.77); // green
            bling->RunRightLEDStrip(0.77);
            autoState = AutoState::teleop;
            break;
        case AutoState::teleop:
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
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            } else if (controller->openClaw()) {
                claw->openClaw();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            }

            // Gear shifting
            if (controller->setLowGear()) {
                driveBase->setLowGear();
                bling->RunLeftLEDStrip(0.69); // yellow
                bling->RunRightLEDStrip(0.69); 
            } else if (controller->setHighGear()) {
                driveBase->setHighGear();
                bling->RunLeftLEDStrip(0.77); // green
                bling->RunRightLEDStrip(0.77);
            }

            // Claw raising and lowering
            if (controller->raiseClaw()) {
                claw->moveClawUp();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            } else if (controller->lowerClaw()) {
                claw->moveClawDown();
                //bling->RunLEDStrip1(0);
                //bling->RunLEDStrip1(0);
            }

            if (controller->holdElevator()) {
                elevator->raiseElevator(-0.3);
            } else {
                elevator->raiseElevator(controller->elevatorSpeed());
            }

            // Cargo out
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
            
            if (controller->setLimelightVisionMode()) {
                driveBase->setLimelightVision();
            } else if (controller->setLimelightCameraMode()) {
                driveBase->setLimelightCamera();
            }

            if (elevator->atMiddle()) {
                //bling->RunLeftLEDStrip(-0.17); // weird shit
                
                //bling->RunRightLEDStrip(-0.17);
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
    }
}